#include "shader/Shader.hpp"
#include "Global.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Object.hpp"

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);    

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Object triangle;
    triangle.InputVertex();

    Shader redShader("S:/GraphicEngine/ruinum_engine/resources/shaders/RedShader.vert", "S:/GraphicEngine/ruinum_engine/resources/shaders/RedShader.frag");
    redShader.Use();
    redShader.SetInt("texture1", 0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
        redShader.Use();

        glm::mat4 view = glm::mat4(1.0f);
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
            triangle.Draw(DrawMode::SOLIDMODE);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}