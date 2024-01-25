#ifndef OBJECT_HPP
#define OBJECT_HPP
#include "RenderObject.hpp"
#include "shader/Shader.hpp"
#include "editor/EditorCamera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object
{
public:
    Object();
	void Draw(EditorCamera);
private:
    Shader _shader{ "RedShader.vert", "RedShader.frag" };
    RenderObject _render;
};

Object::Object() 
{

}

void Object::Draw(EditorCamera camera)
{
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    _shader.SetMat4("projection", projection);
    _shader.SetMat4("view", view);

    _shader.Use();

    _render.BindVAO();
    for (int i = 0; i < 10; i++)
    {
        float angle = 30.0f * i;
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        _shader.SetMat4("model", model);
        _render.Draw(DrawMode::SOLID_MODE);
    }
}
#endif
