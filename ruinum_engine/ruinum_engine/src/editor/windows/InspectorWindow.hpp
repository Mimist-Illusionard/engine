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
	vector <shared_ptr<ComponentDrawer>> _compDrawers;
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

	for (auto drawer : _compDrawers)
	{
		drawer->Draw();
	}

	End();
}

void InspectorWindow::SelectChanged(Entity entity) 
{
	Signature entitySignature = coordinator.GetEntityManager()->GetSignature(entity);

	if (entitySignature.test(coordinator.GetComponentType<TransformComponent>()))
	{
		shared_ptr<TransformComponentDrawer> transformDrawer = make_shared<TransformComponentDrawer>();
		transformDrawer->Set(entity);

		_compDrawers.push_back(transformDrawer);
	}
}

#endif