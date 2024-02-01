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

using namespace glm;

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
    light.GetTransform().Position = vec3(1.2f, 1.0f, 1.2f);
    light.GetTransform().Scale = vec3(0.2, 0.2, 0.2);
    light.GetTransform().Angle = 0;

    Material& lightMaterial = light.GetMaterial();
    lightMaterial.Color = vec3(1.0f, 1.0f, 1.0f);
    lightMaterial.Diffuse = lightMaterial.Color * vec3(0.5f);
    lightMaterial.Ambient = lightMaterial.Color * vec3(0.2f);
    lightMaterial.Specular = vec3(1.0f);
    
    ColorCube colorCube{ "Colors.vert", "Colors.frag" };
    colorCube.GetTransform().Position = vec3(0, 0, 0);

    Material& cubeMaterial = colorCube.GetMaterial();
    cubeMaterial.Ambient = vec3(1.0f, 0.5f, 0.31f);
    cubeMaterial.Diffuse = vec3(1.0f, 0.5f, 0.31f);
    cubeMaterial.Specular = vec3(0.5f, 0.5f, 0.5f);
    cubeMaterial.Shininess = 32.0f;

    colorCube.RefreshMaterial();

    Shader& colorCubeShader = colorCube.GetShader();
    colorCubeShader.SetVec3("light.position", light.GetTransform().Position);
    colorCubeShader.SetVec3("light.ambient", lightMaterial.Ambient);
    colorCubeShader.SetVec3("light.diffuse", lightMaterial.Diffuse);
    colorCubeShader.SetVec3("light.specular", lightMaterial.Specular);

    colorCubeShader.SetVec3("material.specular", 0.5f, 0.5f, 0.5f);
    colorCubeShader.SetFloat("material.shininess", 64.0f);

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