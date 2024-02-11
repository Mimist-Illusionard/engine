#ifndef LIGHTOBJECT_HPP
#define LIGHTOBJECT_HPP

#include "../core/components/TransformComponent.hpp"
#include "../core/components/MaterialComponent.hpp"

#include "../shader/Shader.hpp" 
#include "../RenderObject.hpp"
#include "../editor/EditorCamera.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class LightObject
{
    TransformComponent _transform;
    MaterialComponent _material;
    void SetMaterial(MaterialComponent);

public:
    TransformComponent& GetTransform() { return _transform; }
    MaterialComponent& GetMaterial() { return _material; }
};

void LightObject::SetMaterial(MaterialComponent material)
{
    _material = material;
}
#endif