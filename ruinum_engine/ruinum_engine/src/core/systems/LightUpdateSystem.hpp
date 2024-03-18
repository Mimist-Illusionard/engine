#ifndef LIGHT_UPDATE_SYSTEM
#define LIGHT_UPDATE_SYSTEM

#include "../Components.h"
#include "System.hpp"

class LightUpdateSystem : public System
{
public:
	void Initialize();
	void PostInitialize();
	void Execute();
	void CleanUp();
private:
	LightComponent* _light;
};

void LightUpdateSystem::Initialize()
{
	Signature signature;

	signature.set(coordinator.GetComponentType<ShaderComponent>());
	coordinator.SetSystemSignature<LightUpdateSystem>(signature);
}

void LightUpdateSystem::PostInitialize()
{
	auto lightEntity = coordinator.CreateEntity("Ambient light");
	coordinator.AddComponent(lightEntity, LightComponent(vec3(1.0f, 1.0f, 1.0f), vec3(0.5f), vec3(0.5f), vec3(1.0f)));
	_light = &coordinator.GetComponent<LightComponent>(lightEntity);
}

void LightUpdateSystem::Execute()
{
	Entity cameraEntity;
	if (!coordinator.TryGetEntity<CameraComponent>(cameraEntity)) cout << "Camera entity isn't available";
	CameraComponent& cameraComponent = coordinator.GetComponent<CameraComponent>(cameraEntity);
	vec3& lightPosition = cameraComponent.Camera.Light.GetTransform().Position;

	for (auto const& entity : Entities)
	{
		auto& shaderComponent = coordinator.GetComponent<ShaderComponent>(entity);
		auto& shader = shaderComponent.mShader;

		shader.Use();

		shader.SetVec3("light.ambient", _light->Ambient * _light->Color);
		shader.SetVec3("light.position", lightPosition);
		shader.SetVec3("light.diffuse", _light->Diffuse * _light->Color);
		shader.SetVec3("light.specular", _light->Specular);
	}
}

void LightUpdateSystem::CleanUp() {}
#endif