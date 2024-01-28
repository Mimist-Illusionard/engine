#ifndef TEXTURED_CUBE_HPP
#define TEXTURED_CUBE_HPP

#include "../core/Transform.hpp"
#include "../shader/Shader.hpp"
#include "../RenderObject.hpp"
#include "../editor/EditorCamera.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TexturedCube
{
private:
    Transform _transform;
    Shader _shader { "TextureCube.vert", "TextureCube.frag" };
    RenderObject _render;
public:
    void Draw(EditorCamera);
    void SetPosition(glm::vec3);
    void SetScale(glm::vec3);
    void SetAngle(float);
};

void TexturedCube::Draw(EditorCamera camera)
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
    model = glm::rotate(model, glm::radians(_transform.Angle), glm::vec3(1.0f, 0.3f, 0.5f));
    model = glm::scale(model, _transform.Scale);

    _shader.SetMat4("model", model);
    _render.Draw(DrawMode::SOLID_MODE);
}

void TexturedCube::SetPosition(glm::vec3 position) 
{
    _transform.Position = position;
}

void TexturedCube::SetScale(glm::vec3 scale)
{
    _transform.Scale = scale;
}

void TexturedCube::SetAngle(float angle)
{
    _transform.Angle = angle;
}
#endif
