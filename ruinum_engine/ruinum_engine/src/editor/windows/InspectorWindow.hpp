#ifndef INSPECTOR_WINDOW
#define INSPECTOR_WINDOW

#include "EditorWindow.hpp"
#include "imgui/imgui.h"

#include "../component_drawers/ComponentDrawer.hpp"
#include "../component_drawers/TransformComponentDrawer.hpp"
#include "../../core/observers/ISelectObserver.cpp"

using namespace ImGui;
using namespace std;

class InspectorWindow: EditorWindow, public ISelectObserver
{
public:
	InspectorWindow();
	void Draw();
	void SelectChanged(Entity entity);

private:
	ImGuiWindowFlags _flags;
	vector<ComponentDrawer> _compDrawers;
	char _name;
	bool* _open;

	void Initialize();
};

InspectorWindow::InspectorWindow()
{
	Initialize();
}

void InspectorWindow::Initialize()
{
	_flags |= ImGuiWindowFlags_NoCollapse;
}

void InspectorWindow::Draw()
{
	Begin("Inspector", _open, _flags);
		
	Text("Name: " + _name);

	for (auto it = begin(_compDrawers); it != end(_compDrawers); ++it) {
		it->Draw();
		cout << "Draw drawer" << endl;
	}

	End();
}

void InspectorWindow::SelectChanged(Entity entity) 
{
	cout << "Select changed";

	Signature entitySignature = coordinator.GetEntityManager()->GetSignature(entity);

	if (entitySignature.test(coordinator.GetComponentType<TransformComponent>()))
	{
		//cout << "Transform component on " << entity << endl;
		TransformComponentDrawer transformDrawer;
		transformDrawer.Set(entity);

		cout << "transfprm setted";

		_compDrawers.push_back(transformDrawer);
	}
}

#endif