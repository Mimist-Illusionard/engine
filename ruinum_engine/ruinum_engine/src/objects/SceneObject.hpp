#ifndef SCENEOBJECT_HPP
#define SCENEOBJECT_HPP

#include "../core/Transform.hpp"
#include "../shader/Shader.hpp"
#include "../RenderObject.hpp"
#include "../editor/EditorCamera.hpp"

#include "Object.hpp"

class SceneObject : public Object
{
public:
    SceneObject(const char* vert, const char* frag) : Object(vert, frag) {};
};
#endif