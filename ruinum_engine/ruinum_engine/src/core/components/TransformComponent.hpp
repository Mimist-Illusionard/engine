#ifndef TRANSFORM_COMPONENT
#define TRANSFORM_COMPONENT

#include <glm/glm.hpp>

using namespace glm;

struct TransformComponent
{
	vec3 Position = vec3(0, 0, 0);;
	vec3 Scale = vec3(1, 1, 1);
	float Angle = 0; //TODO: Change angle to an actual vec3 rotation

	TransformComponent() { }
	TransformComponent(vec3 position, vec3 scale, float angle)
	{
		Position = position;
		Scale = scale;
		Angle = angle;
	}
};

#endif