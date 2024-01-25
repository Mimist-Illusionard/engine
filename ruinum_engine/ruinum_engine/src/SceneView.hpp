#ifndef SCENE_VIEW_HPP
#define SCENE_VIEW_HPP
#include "Object.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

class SceneView
{
	Object object;
	//GLFWwindow* Window;
	EditorCamera camera;
public:
	//SceneView(GLFWwindow* window) { Window = window; }
	void MainCycle(GLFWwindow*);
};

void SceneView::MainCycle(GLFWwindow* Window)
{
	while (!glfwWindowShouldClose(Window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwSwapBuffers(Window);
		glfwPollEvents();
	}
}

#endif // !SCENE_VIEW_HPP
