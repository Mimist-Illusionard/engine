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
    Shader shader{ "RedShader.vert", "RedShader.frag" };
	RenderObject test;
public:
    Object();
	void Draw(EditorCamera);
};

void Object::Draw(EditorCamera camera)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.Use();
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    shader.SetMat4("projection", projection);
    shader.SetMat4("view", view);

    test.BindVAO();
    for (int i = 0; i < 10; i++)
    {
        float angle = 30.0f * i;
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shader.SetMat4("model", model);
        test.Draw(DrawMode::SOLID_MODE);
    }
}
#endif // OBJECT_HPP
