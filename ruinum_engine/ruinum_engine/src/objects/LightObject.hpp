#ifndef LIGHTOBJECT_HPP
#define LIGHTOBJECT_HPP

#include "../core/Transform.hpp"
#include "../core/Material.hpp"
#include "../shader/Shader.hpp"
#include "../RenderObject.hpp"
#include "../editor/EditorCamera.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class LightObject
{
    Transform _transform;
    Material _material;
    void SetMaterial(Material);

public:
    Transform& GetTransform() { return _transform; }
    Material& GetMaterial() { return _material; }
};


void LightObject::SetMaterial(Material material)
{
    _material = material;
}
#endif