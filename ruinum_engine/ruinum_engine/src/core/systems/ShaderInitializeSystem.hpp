#ifndef SHADER_INITIALIZE_SYSTEM
#define SHADER_INITIALIZE_SYSTEM

#include "System.hpp"

#include "../Components.h"
#include "System.hpp"


class ShaderInitializeSystem: public System
{
public:
	void Initialize();
	void Execute();
	void CleanUp();
};

void ShaderInitializeSystem::Initialize()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<ShaderComponent>());
	signature.set(coordinator.GetComponentType<MaterialComponent>());
	coordinator.SetSystemSignature<ShaderInitializeSystem>(signature);	
}

void ShaderInitializeSystem::Execute()
{
	for (auto const& entity : Entities)
	{
		auto& materialComponent = coordinator.GetComponent<MaterialComponent>(entity);
		auto& shaderComponent = coordinator.GetComponent<ShaderComponent>(entity);
		
		auto& shader = shaderComponent.mShader;		

		shader.SetVec3("material.ambient", materialComponent.Ambient);
		shader.SetVec3("material.diffuse", materialComponent.Diffuse);
		shader.SetVec3("material.specular", materialComponent.Specular);
		shader.SetFloat("material.shininess", materialComponent.Shininess);
	}
}

void ShaderInitializeSystem::CleanUp()
{
	Entities.clear();
}

#endif