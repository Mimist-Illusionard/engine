#ifndef TRANSFORM
#define TRANSFORM

#include <glm/glm.hpp>

struct Transform
{
	glm::vec3 Position;
	glm::vec3 Scale = glm::vec3(1, 1, 1);
	float Angle = 0; //TODO: Change angle to an actual vec3 rotation
};

#endif