#ifndef RENDER_INITIALIZE_SYSTEM
#define RENDER_INITIALIZE_SYSTEM

#include <list>

#include "../Components.h"
#include "System.hpp"

class RenderInitializeSystem : public System
{
public:
	void Initialize();
	void Execute();
	void CleanUp();

private:
	std::list<Entity> _cleanUpEntities;
};

void RenderInitializeSystem::Initialize()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<VerticesComponent>());
	signature.set(coordinator.GetComponentType<RenderInitializeComponent>());
	coordinator.SetSystemSignature<RenderInitializeSystem>(signature);
}

void RenderInitializeSystem::Execute()
{
	for (auto const& entity : Entities)
	{
		_cleanUpEntities.push_back(entity);

		auto& verticesComponent = coordinator.GetComponent<VerticesComponent>(entity);

		glGenBuffers(1, &verticesComponent.VBO);
		glGenVertexArrays(1, &verticesComponent.VAO);

		glBindVertexArray(verticesComponent.VAO);

		glBindBuffer(GL_ARRAY_BUFFER, verticesComponent.VBO);
		glBufferData(GL_ARRAY_BUFFER, verticesComponent.Size, verticesComponent.Vertices, GL_STATIC_DRAW);

		glBindVertexArray(verticesComponent.VAO);
		//vertices
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//texture
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}

void RenderInitializeSystem::CleanUp() 
{
	for (Entity entity : _cleanUpEntities)
	{				
		coordinator.RemoveComponent<RenderInitializeComponent>(entity);
		coordinator.AddComponent(entity, RenderComponent());
	}

	Entities.clear();
	_cleanUpEntities.clear();
}

#endif