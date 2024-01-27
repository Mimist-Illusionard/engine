#ifndef CUBE_HPP
#define CUBE_HPP
#include "RenderObject.hpp"
#include "shader/Shader.hpp"
#include "editor/EditorCamera.hpp"
#include "core/Transform.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object
{
private:
    Transform _transform;
    Shader _shader { "RedShader.vert", "RedShader.frag" };
    RenderObject _render;
public:
    Object(Transform);
    void Draw(EditorCamera);
    void SetPosition(glm::vec3);
    void SetAngle(float);
    Transform GetTransform() { return _transform; }
};

void Object::Draw(EditorCamera camera)
{
    _shader.Use();
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    _shader.SetMat4("projection", projection);
    _shader.SetMat4("view", view);

    _render.BindVAO();

    float angle = 30.0f;
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, _transform.Position);
    model = glm::rotate(model, glm::radians(_transform.Angle), glm::vec3(1.0f, 0.3f, 0.5f));
    _shader.SetMat4("model", model);
    _render.Draw(DrawMode::SOLID_MODE);
}

void Object::SetPosition(glm::vec3 position) 
{
    _transform.Position = position;
}

void Object::SetAngle(float angle)
{
    _transform.Angle = angle;
}

Object::Object(Transform transform)
{
    _transform = transform;
}
#endif
