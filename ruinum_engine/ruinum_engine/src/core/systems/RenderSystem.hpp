#ifndef RENDER_SYSTEM
#define RENDER_SYSTEM

#include "System.hpp"

#include "../ECS.h"
#include "../Coordinator.hpp"
#include "../../Global.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class RenderSystem: public System
{
public:
	void Initialize();
	void Execute();
};

void RenderSystem::Initialize()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<VerticesComponent>());
	signature.set(coordinator.GetComponentType<MaterialComponent>());
	signature.set(coordinator.GetComponentType<ShaderComponent>());
	signature.set(coordinator.GetComponentType<TransformComponent>());
	signature.set(coordinator.GetComponentType<RenderComponent>());
	coordinator.SetSystemSignature<RenderSystem>(signature);
}

void RenderSystem::Execute()
{
	//cout << "Render System entities amout: " << Entities.size() << endl;
	if (Entities.size() <= 0) return;

	Entity cameraEntity;
	if (!coordinator.TryGetEntity<CameraComponent>(cameraEntity)) return; 
	CameraComponent& camera = coordinator.GetComponent<CameraComponent>(cameraEntity);

	//std::cout << "Position:" << camera.Camera.Position.x << "," << camera.Camera.Position.y << "," << camera.Camera.Position.z << std::endl;

	for (auto const& entity : Entities)
	{
		auto& verties = coordinator.GetComponent<VerticesComponent>(entity);
		auto& material = coordinator.GetComponent<MaterialComponent>(entity);
		auto& shader = coordinator.GetComponent<ShaderComponent>(entity);
		auto& transform = coordinator.GetComponent<TransformComponent>(entity);

		shader.mShader.Use();

		mat4 view = camera.Camera.GetViewMatrix();
		mat4 projection = perspective(glm::radians(camera.Camera.Fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		view = translate(view, vec3(0.0f, 0.0f, -3.0f));

		shader.mShader.SetMat4("projection", projection);
		shader.mShader.SetMat4("view", view);

		glBindVertexArray(verties.VAO);

		mat4 model = glm::mat4(1.0f);
		model = translate(model, transform.Position);
		model = rotate(model, glm::radians(transform.Angle), glm::vec3(1.0f, 1.0f, 1.0f));
		model = scale(model, transform.Scale);

		shader.mShader.SetMat4("model", model);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

#endif