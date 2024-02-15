#ifndef COMPONENT_REGISTER
#define COMPONENT_REGISTER

#include "Components.h"
#include "Coordinator.hpp"

extern Coordinator coordinator;

class ComponentRegister
{
public:
	void Initialize();
};


void ComponentRegister::Initialize()
{
	coordinator.RegisterComponent<TransformComponent>();
	coordinator.RegisterComponent<CameraComponent>();

	coordinator.RegisterComponent<VerticesComponent>();
	coordinator.RegisterComponent<ShaderComponent>();
	coordinator.RegisterComponent<MaterialComponent>();
	
	coordinator.RegisterComponent<RenderInitializeComponent>();
	coordinator.RegisterComponent<RenderComponent>();
}

#endif