#ifndef OPEN_GL_WINDOW
#define OPEN_GL_WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Global.h"
#include "shader/Shader.hpp"
#include "Object.hpp"
#include "editor/EditorCamera.hpp"

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
    Object triangle;
    triangle.InputVertex();

    Shader redShader("RedShader.vert", "RedShader.frag");
    redShader.Use();
    redShader.SetInt("texture1", 0);

    while (!glfwWindowShouldClose(window))
    {;
        float currentFrame = static_cast<float>(glfwGetTime());
        _deltaTime = currentFrame - _lastFrame;
        _lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Input(window);

        redShader.Use();
        glm::mat4 view = _camera.GetViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        redShader.SetMat4("projection", projection);
        redShader.SetMat4("view", view);

        triangle.BindVAO();
        for (int i = 0; i < 10; i++)
        {
            float angle = 30.0f * i;
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            redShader.SetMat4("model", model);
            triangle.Draw(DrawMode::SOLID_MODE);
        }

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