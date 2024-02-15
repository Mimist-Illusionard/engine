#ifndef RUINUM_EDITOR
#define RUINUM_EDITOR

#include "windows/SceneHierarchyWindow.hpp"
#include "windows/InspectorWindow.hpp"

class RuinumEditor
{
public:
	void Initialize(EntityManager&);
	void Draw();

private:
	Coordinator _coordinator;
	SceneHierarchyWindow _sceneHierarchyWindow;
	InspectorWindow _inspectorWindow;
};

void RuinumEditor::Initialize(EntityManager& entityManager)
{
	SceneHierarchyWindow sceneHierarchyWindow;
	_sceneHierarchyWindow = sceneHierarchyWindow;

	InspectorWindow inspectorWindow;
	_inspectorWindow = inspectorWindow;

	entityManager.AddObserver(&_sceneHierarchyWindow);
}

void RuinumEditor::Draw()
{
	_sceneHierarchyWindow.Draw();
	_inspectorWindow.Draw();
}

#endif