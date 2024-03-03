#ifndef LIGHT_UPDATE_SYSTEM
#define LIGHT_UPDATE_SYSTEM

#include "../Components.h"
#include "System.hpp"

class LightUpdateSystem : public System
{
public:
	void Initialize();
	void Execute();
	void CleanUp();
private:
	MaterialComponent _lightMaterial;
};

void LightUpdateSystem::Initialize()
{
	Signature signature;

	signature.set(coordinator.GetComponentType<ShaderComponent>());
	coordinator.SetSystemSignature<LightUpdateSystem>(signature);

	_lightMaterial.Color = vec3(1.0f, 1.0f, 1.0f);
	_lightMaterial.Diffuse = _lightMaterial.Color * vec3(0.5f);
	_lightMaterial.Ambient = _lightMaterial.Color * vec3(0.5f);
	_lightMaterial.Specular = vec3(1.0f);
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

		shader.SetVec3("light.ambient", _lightMaterial.Ambient);
		shader.SetVec3("light.position", lightPosition);
		shader.SetVec3("light.diffuse", _lightMaterial.Diffuse);
		shader.SetVec3("light.specular", _lightMaterial.Specular);
	}
}

void LightUpdateSystem::CleanUp()
{
}

#endif