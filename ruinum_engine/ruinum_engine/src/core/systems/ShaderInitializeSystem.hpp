#ifndef SHADER_INITIALIZE_SYSTEM
#define SHADER_INITIALIZE_SYSTEM

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
		auto& shaderComponent = coordinator.GetComponent<ShaderComponent>(entity);
		auto& materialComponent = coordinator.GetComponent<MaterialComponent>(entity);
		
		auto& shader = shaderComponent.mShader;

		shader.Use();

		shader.SetVec3("material.diffuse", materialComponent.Diffuse);
		shader.SetVec3("material.specular", materialComponent.Specular);
		shader.SetFloat("material.shininess", materialComponent.Shininess);	

		if (shaderComponent.Diffuse != "") LoadTexture(shaderComponent.Diffuse, GL_TEXTURE0);
		if (shaderComponent.Specular != "") LoadTexture(shaderComponent.Specular, GL_TEXTURE1);

		shader.SetInt("material.diffuse", 0);
		shader.SetInt("material.specular", 1);
	}
}

void ShaderInitializeSystem::CleanUp()
{
	Entities.clear();
}

#endif