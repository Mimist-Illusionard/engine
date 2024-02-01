#ifndef COLOR_CUBE_HPP
#define COLOR_CUBE_HPP

#include "Object.hpp"
#include "../core/Material.hpp"

class ColorCube: public Object
{
public:
    ColorCube(const char* vert, const char* frag) : Object(vert, frag)
    {
        _shader.Use();
        _shader.SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
        _shader.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);      
    }

    void DrawLogic(EditorCamera camera);
    void MaterialSetted(Material material);
};

void ColorCube::DrawLogic(EditorCamera camera)
{
    _shader.SetVec3("viewPos", camera.Position);
}

void ColorCube::MaterialSetted(Material material) 
{
    _material = material;

    _shader.SetVec3("material.ambient", _material.Ambient);
    _shader.SetVec3("material.diffuse", _material.Diffuse);
    _shader.SetVec3("material.specular", _material.Specular);
    _shader.SetFloat("material.shininess", _material.Shininess);
}
#endif