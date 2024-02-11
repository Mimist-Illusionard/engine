#ifndef MATERIAL_COMPONENT
#define MATERIAL_COMPONENT

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>

using namespace glm;

struct MaterialComponent 
{
    vec3 Color = vec3(1, 1, 1);
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    
    float Shininess;

    MaterialComponent() {}
    MaterialComponent(vec3 color, vec3 ambient, vec3 diffuese, vec3 specular, float shininess)
    {
        Color = color;
        Ambient = ambient;
        Diffuse = diffuese;
        Specular = specular;

        Shininess = shininess;
    }
};

#endif