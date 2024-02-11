#ifndef OPEN_GL_WINDOW
#define OPEN_GL_WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Global.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "shader/Shader.hpp"
#include "objects/SceneObject.hpp"
#include "objects/ColorCube.hpp" 

#include "editor/EditorCamera.hpp"
#include "editor/windows/SceneHierarchyWindow.hpp"
#include "editor/windows/InspectorWindow.hpp"

#include "core/RuinumManager.hpp"

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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    return window;
}

void OpenGLWindow::Render(GLFWwindow* window)
{
    RuinumManager ruinumManager;
    ruinumManager.Initialize();

    //Entity cameraEntity = coordinator.CreateEntity();
    //coordinator.AddComponent(cameraEntity, CameraComponent(Camera));

    Entity cubeEntity = coordinator.CreateEntity();
    coordinator.AddComponent(cubeEntity, RenderInitializeComponent());
    coordinator.AddComponent(cubeEntity, VerticesComponent());
    coordinator.AddComponent(cubeEntity, ShaderComponent("Colors.vert", "Colors.frag"));

    //Entity entity = coordinator.CreateEntity();
    //coordinator.AddComponent(entity, RenderComponent());

    /* Entity cube = coordinator.CreateEntity();
    coordinator.AddComponent(cube, TransformComponent(vec3(0, 3, 0), vec3(1, 1, 1), 45));
    coordinator.AddComponent(cube, MaterialComponent(vec3(1, 1, 1), vec3(1.0f, 0.5f, 0.31f), vec3(1.0f, 0.5f, 0.31f), vec3(0.5f, 0.5f, 0.5f), 32.0f ));
    coordinator.AddComponent(cube, ShaderComponent("Colors.vert", "Colors.frag"));
    coordinator.AddComponent(cube, RenderInitializerComponent());
    coordinator.AddComponent(cube, RenderComponent());*/

    //Light
    LightObject light = Camera.Light;

    //cube
    ColorCube colorCube{ "Colors.vert", "Colors.frag" };

    //cube settings
    colorCube.GetTransform().Position = vec3(0, 0, 0);
    colorCube.GetRender().LoadDiffuse("container.jpg");
    colorCube.GetRender().LoadSpecular("container_specular.jpg");
    colorCube.SetObjectMaterial({ 1.0f, 0.5f, 0.31f }, { 1.0f, 0.5f, 0.31f }, { 0.5f, 0.5f, 0.5f }, 32.0f);
    colorCube.ShaderSetLighting(light.GetTransform().Position, light.GetMaterial().Ambient, light.GetMaterial().Diffuse, light.GetMaterial().Specular);

    //shader settings
    Shader& colorCubeShader = colorCube.GetShader();
    colorCubeShader.SetInt("material.diffuse", 0);
    colorCubeShader.SetInt("material.specular", 1);

    SceneHierarchyWindow sceneHierarchyWindow;
    //TODO: Make an actual object connection on view and in hierarchy window
    sceneHierarchyWindow.AddObject("light_0", "Light");
    sceneHierarchyWindow.AddObject("color_cube_0", "Color Cube");
    sceneHierarchyWindow.AddObject("main_camera", "Camera");

    InspectorWindow inspectorWindow;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        _deltaTime = currentFrame - _lastFrame;
        _lastFrame = currentFrame;

        glClearColor(0.4f, 0.3f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //ImGui::ShowDemoWindow();

        ruinumManager.Execute();

        colorCube.Draw(Camera);
        sceneHierarchyWindow.Draw();
        inspectorWindow.Draw();

        Input(window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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