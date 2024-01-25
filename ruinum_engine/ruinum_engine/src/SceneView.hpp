#ifndef SCENE_VIEW_HPP
#define SCENE_VIEW_HPP
#include "Object.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

class SceneView
{
public:
	void Initialize(EditorCamera camera);
	void RenderScene(GLFWwindow*);
private:
	Object _object;
	EditorCamera _camera;
};

void SceneView::Initialize(EditorCamera camera) 
{
	_camera = camera;
	_object = Object();
}

void SceneView::RenderScene(GLFWwindow* Window)
{
	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_object.Draw(_camera);

	glfwSwapBuffers(Window);
	glfwPollEvents();
}
#endif
