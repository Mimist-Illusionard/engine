#ifndef OPEN_GL_WINDOW
#define OPEN_GL_WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Global.h"
#include "shader/Shader.hpp"
#include "editor/EditorCamera.hpp"
#include "core/Transform.hpp"
#include "objects/SceneObject.hpp"
#include "objects/ColorCube.hpp"

EditorCamera Camera{ { 0.0f, 0.0f, 4.0f } };

void FramebufferCallback(GLFWwindow* window, int width, int height);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

class OpenGLWindow
{
public:    
    GLFWwindow* CreateWindow();
	void Render(GLFWwindow* window);

private:
    float _deltaTime = 0.0f;
    float _lastFrame = 0.0f;

    void Input(GLFWwindow* window);
};

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

    glfwSetFramebufferSizeCallback(window, FramebufferCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetScrollCallback(window, ScrollCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);

    return window;
}

void OpenGLWindow::Render(GLFWwindow* window)
{  
    SceneObject light{ "LightCube.vert", "LightCube.frag" };
    light.GetTransform().Position = glm::vec3(1.2f, 1.0f, 1.2f);
    light.GetTransform().Scale = glm::vec3(0.2, 0.2, 0.2);
    light.GetTransform().Angle = 0;
    
    ColorCube colorCube{ "Colors.vert", "Colors.frag" };
    colorCube.GetTransform().Position = glm::vec3(0, 0, 0);
    colorCube.GetShader().SetVec3("lightPos", light.GetTransform().Position);

    SceneObject cube{ "TextureCube.vert", "TextureCube.frag" };
    while (!glfwWindowShouldClose(window))
    {;
        float currentFrame = static_cast<float>(glfwGetTime());
        _deltaTime = currentFrame - _lastFrame;
        _lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        light.Draw(Camera);
        colorCube.Draw(Camera);

        for (int i = 0; i < 10; i++)
        {
            Transform& cubeTransform = cube.GetTransform();
            cubeTransform.Position = cubePositions[i];
            cubeTransform.Angle = 30 * i;

            //cube.Draw(Camera);
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
        Camera.ProcessKeyboard(FORWARD, _deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Camera.ProcessKeyboard(BACKWARDS, _deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Camera.ProcessKeyboard(LEFT, _deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Camera.ProcessKeyboard(RIGHT, _deltaTime);
}

void FramebufferCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    Camera.ProcessMouseLook(xposIn, yposIn);    
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    Camera.ProcessMouseScroll(yoffset);
}

#endif