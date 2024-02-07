#ifndef MATERIAL
#define MATERIAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>

using namespace glm;

struct Material 
{
    vec3 Color;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    
    float Shininess;
};

#endif