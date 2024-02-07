#ifndef INSPECTOR_WINDOW
#define INSPECTOR_WINDOW

#include "EditorWindow.hpp"
#include "imgui/imgui.h"

using namespace ImGui;
using namespace std;

class InspectorWindow: EditorWindow
{
public:
	InspectorWindow();
	void Draw();
	void SetObject();

private:
	ImGuiWindowFlags _flags;
	void Initialize();
	bool* _open;
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
	

	End();
}

#endif