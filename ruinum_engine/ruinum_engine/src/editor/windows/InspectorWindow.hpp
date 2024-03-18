#ifndef INSPECTOR_WINDOW
#define INSPECTOR_WINDOW

#include "EditorWindow.hpp"
#include "imgui/imgui.h"

#include <map>

#include "../component_drawers/Drawers.h"
#include "../src/extentions/EntityExtentions.h"
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
	vector<shared_ptr<ComponentDrawer>> _compDrawers; //Make map and take drawers to this vector instead of creating new object
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

//TODO: Make more lightweight and easier drawer implementer
//NOT hard coding
void InspectorWindow::SelectChanged(Entity entity)
{
	_compDrawers.clear();
	
	if (HasComponent<TransformComponent>(entity)) 
	{
		shared_ptr<TransformComponentDrawer> transformDrawer = make_shared<TransformComponentDrawer>();
		transformDrawer->Set(entity);

		_compDrawers.push_back(transformDrawer);
	}

	if (HasComponent<MaterialComponent>(entity))
	{
		shared_ptr<MaterialComponentDrawer> materialDrawer = make_shared<MaterialComponentDrawer>(); 
		materialDrawer->Set(entity);

		_compDrawers.push_back(materialDrawer);
	}

	if (HasComponent<LightComponent>(entity))
	{
		shared_ptr<LightComponentDrawer> materialDrawer = make_shared<LightComponentDrawer>();
		materialDrawer->Set(entity);

		_compDrawers.push_back(materialDrawer);
	}
}

#endif