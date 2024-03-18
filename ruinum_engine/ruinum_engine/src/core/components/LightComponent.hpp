#ifndef LIGHT_COMPONENT
#define LIGHT_COMPONENT

struct LightComponent
{
    vec3 Color;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    LightComponent(){}
    LightComponent(vec3 color, vec3 ambient, vec3 diffuse, vec3 specular) 
    {
        Color = color;
        Ambient = ambient;
        Diffuse = diffuse;
        Specular = specular;
    }
};

#endif