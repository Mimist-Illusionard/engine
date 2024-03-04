#ifndef SCENE_HIERARCHY_WINDOW
#define SCENE_HIERARCHY_WINDOW

#include "EditorWindow.hpp"
#include "InspectorWindow.hpp"

#include "imgui/imgui.h"
#include "../../core/ECS.h"

#include <stdio.h>
#include <guiddef.h>
#include <map>

using namespace ImGui;
using namespace std;

class SceneHierarchyWindow: public EditorWindow, public IEntityObserver
{
public:
	SceneHierarchyWindow();
	void SetInspectorWindow(InspectorWindow);
	void Draw();
	void AddObject(char*, Entity);
	void RemoveObject(char*);
	
	void EntityCreated(Entity, char const*);
	void EntityDestoryed(Entity);

private:
	InspectorWindow* _inspectorWindow;
	ImGuiWindowFlags _flags;
	map<char*, Entity> _objects;
	int _objectsSize = 0;
	int _selected = -1;
	bool* _open;

	void Initialize();
};

SceneHierarchyWindow::SceneHierarchyWindow() 
{
	Initialize();
}

void SceneHierarchyWindow::SetInspectorWindow(InspectorWindow inspectorWindow)
{
	_inspectorWindow = &inspectorWindow;
}

void SceneHierarchyWindow::Initialize()
{
	_flags |= ImGuiWindowFlags_NoCollapse;
}

void SceneHierarchyWindow::Draw()
{
	Begin("Scene Hierarchy", _open, _flags);

	int counter = 0;
	for (map<char*, Entity>::iterator i = _objects.begin(); i != _objects.end(); ++i)
	{
		if (Selectable(i->first, _selected == counter))
		{
			_selected = counter;
			_inspectorWindow->SetEntity(i->second);
		}
		counter++;
	}

	End();
}

void SceneHierarchyWindow::AddObject(char* key, Entity entity)
{
	_objects.insert(pair<char*, Entity>(key, entity));
	_objectsSize++;
}

void SceneHierarchyWindow::RemoveObject(char* key)
{
	_objects.erase(key);
	_objectsSize--;
}

void SceneHierarchyWindow::EntityCreated(Entity entity, const char* name)
{
	AddObject((char*)name, entity);
}

void SceneHierarchyWindow::EntityDestoryed(Entity entity)
{
	for (map<char*, Entity>::iterator i = _objects.begin(); i != _objects.end(); ++i)
	{
		if (i->second == entity) RemoveObject(i->first);
	}
}
#endif