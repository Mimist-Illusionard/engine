#ifndef CAMERA_HPP
#define CAMERA_HPP 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//camera default settings
const float PITCH = 0.0f; // x/z rotate
const float YAW   = -90.0f; //x&z / y rotate
const float CAMERA_SPEED = 2;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 WorldUp(0.0f, 1.0f, 0.0f);

enum Camera_movement
{
	FORWARD = 1,
	BACKWARD = 2,
	LEFT = 3,
	RIGHT = 4,
};

class Camera
{
public:
	glm::vec3 Pos;
	glm::vec3 Pointer;
	glm::vec3 Up;
	glm::vec3 Right;

	float yaw;
	float pitch;

	Camera(glm::vec3);

	void CameraPosUpdate(Camera_movement);
	void CameraMouseRotate(float, float);
	void CameraVecUpdate();
	glm::mat4 SetViewMatix();
};

Camera::Camera(glm::vec3 pos)
{
	Pos = pos;
	yaw = YAW;
	pitch = PITCH;
	CameraVecUpdate();
}

void Camera::CameraPosUpdate(Camera_movement direction)
{
	float velocity = CAMERA_SPEED * deltaTime;
	switch (direction)
	{
		case FORWARD: Pos += velocity * Pointer;
		case BACKWARD: Pos -= velocity * Pointer;
		case LEFT: Pos -= velocity * Pointer;
		case RIGHT: Pos += velocity * Pointer;
	}
}

void Camera::CameraMouseRotate(float xoffset, float yoffset)
{
	xoffset *= SENSITIVITY;
	yoffset *= SENSITIVITY;

	yaw += xoffset;
	pitch += yoffset;

	CameraVecUpdate();
}

void Camera::CameraVecUpdate()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	Pointer = glm::normalize(direction);
	Right = glm::cross(Pointer, WorldUp);
	Up = glm::cross(Pointer, Right);
}

glm::mat4 Camera::SetViewMatix()
{
	return glm::lookAt(Pos, Pos + Pointer, Up);
}

#endif