#ifndef EDITOR_CAMERA_HPP
#define EDITOR_CAMERA_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "objects/LightObject.hpp"

enum Input 
{
    FORWARD,
    BACKWARDS,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class EditorCamera
{
public:
    LightObject Light;

    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Fov;

    float FirstInput = true;
    float LastX = 800.0f / 2.0;
    float LastY = 600.0 / 2.0;

    glm::mat4 GetViewMatrix() { return glm::lookAt(Position, Position + Front, Up); }
    void ProcessKeyboard(Input direction, float deltaTime);
    void ProcessMouseScroll(float yoffset);
    void ProcessMouseLook(double x, double y);
    void ProcessMouseMovement(float xoffset, float yoffset);

    EditorCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    ~EditorCamera() {};

private:
    void UpdateLightPos() { Light.GetTransform().Position = Position; }
    void UpdateCameraVectors();
};

EditorCamera::EditorCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    
    //light settings
    Material& lightMaterial = Light.GetMaterial();
    lightMaterial.Color = vec3(1.0f, 1.0f, 1.0f);
    lightMaterial.Diffuse = lightMaterial.Color * vec3(0.5f);
    lightMaterial.Ambient = lightMaterial.Color * vec3(0.2f);
    lightMaterial.Specular = vec3(1.0f);

    UpdateCameraVectors();
}

void EditorCamera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));

    UpdateLightPos();
}

void EditorCamera::ProcessKeyboard(Input direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARDS)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

void EditorCamera::ProcessMouseScroll(float yoffset)
{
    Fov -= (float)yoffset;
    if (Fov < 1.0f)
        Fov = 1.0f;
    if (Fov > 45.0f)
        Fov = 45.0f;
}

void EditorCamera::ProcessMouseLook(double x, double y)
{    
    float xpos = static_cast<float>(x);
    float ypos = static_cast<float>(y);

    if (FirstInput)
    {
        LastX = xpos;
        LastY = ypos;
        FirstInput = false;
    }

    float xoffset = xpos - LastX;
    float yoffset = LastY - ypos;
    LastX = xpos;
    LastY = ypos;

    ProcessMouseMovement(xoffset, yoffset);

    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
}

void EditorCamera::ProcessMouseMovement(float xoffset, float yoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    UpdateCameraVectors();
}
#endif