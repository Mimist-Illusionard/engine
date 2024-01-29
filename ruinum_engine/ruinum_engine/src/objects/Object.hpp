#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "../core/Transform.hpp"
#include "../shader/Shader.hpp"
#include "../RenderObject.hpp"
#include "../editor/EditorCamera.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Object
{
protected:
    Transform _transform;
    Shader _shader;
    RenderObject _render;
public:
    Object(const char*, const char*);
	void Draw(EditorCamera);

    Shader& GetShader() { return _shader; }
    Transform& GetTransform() { return _transform; }
};

Object::Object(const char* vert, const char* frag)
{
    Shader shaderWithPath{ vert, frag };
    _shader = shaderWithPath;
}

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

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, _transform.Position);
    model = glm::rotate(model, glm::radians(_transform.Angle), glm::vec3(1.0f, 1.0f, 1.0f));
    model = glm::scale(model, _transform.Scale);

    _shader.SetMat4("model", model);
    _render.Draw(DrawMode::SOLID_MODE);
}
#endif //OBJECT_HPP