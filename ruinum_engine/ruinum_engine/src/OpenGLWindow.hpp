#ifndef OPEN_GL_WINDOW
#define OPEN_GL_WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Global.h"
#include "shader/Shader.hpp"
#include "editor/EditorCamera.hpp"
#include "Object.hpp"

class OpenGLWindow
{
public:
	OpenGLWindow();
	~OpenGLWindow();

    GLFWwindow* CreateWindow();
	void Render(GLFWwindow* window);

private:
    EditorCamera _camera { { 0.0f, 0.0f, 4.0f } };
    float _deltaTime = 0.0f;
    float _lastFrame = 0.0f;

    void Input(GLFWwindow* window);
};

OpenGLWindow::OpenGLWindow()
{
}

OpenGLWindow::~OpenGLWindow()
{
}

GLFWwindow* OpenGLWindow::CreateWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Ruinum Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);

    return window;
}

void OpenGLWindow::Render(GLFWwindow* window)
{  
    Transform transform;
    transform.Position = glm::vec3(0.0f, 0.0f, 0.0f);
    transform.Angle = 30;
    Object cube(transform);

    while (!glfwWindowShouldClose(window))
    {;
        float currentFrame = static_cast<float>(glfwGetTime());
        _deltaTime = currentFrame - _lastFrame;
        _lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (int i = 0; i < 10; i++)
        {
            cube.SetPosition(cubePositions[i]);
            cube.SetAngle(30 * i);

            cube.Draw(_camera);
        }

        Input(window);       

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void OpenGLWindow::Input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        _camera.ProcessKeyboard(FORWARD, _deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        _camera.ProcessKeyboard(BACKWARDS, _deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        _camera.ProcessKeyboard(LEFT, _deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        _camera.ProcessKeyboard(RIGHT, _deltaTime);
}
#endif