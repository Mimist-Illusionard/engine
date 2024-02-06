#ifndef SCENE_HIERARCHY_WINDOW
#define SCENE_HIERARCHY_WINDOW

#include "EditorWindow.hpp"
#include "imgui/imgui.h"

#include <stdio.h>
#include <guiddef.h>
#include <map>

using namespace ImGui;
using namespace std;

class SceneHierarchyWindow: public EditorWindow
{
public:
	SceneHierarchyWindow();
	void Draw();
	void AddObject(char*, char*);
	void AddObject(const char*, const char*);
	void RemoveObject(char*);
private:
	ImGuiWindowFlags _flags;
	map<char*, char*> _objects;
	int _objectsSize = 0;
	int _selected = -1;
	bool* _open;

	void Initialize();
};

SceneHierarchyWindow::SceneHierarchyWindow() 
{
	Initialize();
}

void SceneHierarchyWindow::Initialize()
{
	_flags |= ImGuiWindowFlags_NoCollapse;
}

void SceneHierarchyWindow::Draw()
{
	Begin("Scene Hierarchy", _open, _flags);

	int counter = 0;
	for (map<char*, char*>::iterator i = _objects.begin(); i != _objects.end(); ++i)
	{
		if (Selectable(i -> second, _selected == counter))
			_selected = counter;
		counter++;
	}

	End();	
}

void SceneHierarchyWindow::AddObject(const char* key, const char* name)
{
	AddObject((char*)key, (char*)name);
}

void SceneHierarchyWindow::AddObject(char* key, char* name)
{
	_objects.insert(pair<char*, char*>(key, name));
	_objectsSize++;
}

void SceneHierarchyWindow::RemoveObject(char* key)
{
	_objects.erase(key);
	_objectsSize--;
}
#endif