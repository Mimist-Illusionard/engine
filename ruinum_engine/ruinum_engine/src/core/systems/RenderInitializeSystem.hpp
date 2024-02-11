#ifndef RENDER_INITIALIZE_SYSTEM
#define RENDER_INITIALIZE_SYSTEM

#include "../Components.h"
#include "System.hpp"

class RenderInitializeSystem : public System
{
public:
	void Initialize();
	void Execute();
};

void RenderInitializeSystem::Initialize()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<VerticesComponent>());
	signature.set(coordinator.GetComponentType<ShaderComponent>());
	signature.set(coordinator.GetComponentType<RenderInitializerComponent>());
	coordinator.SetSystemSignature<RenderInitializeSystem>(signature);
}

void RenderInitializeSystem::Execute()
{
	cout << Entities.size() << endl;

	//for (auto const& entity : Entities)
	//{
	//	cout << "RenderInitializeSystem Execute";

	//	auto& vertices = coordinator.GetComponent<VerticesComponent>(entity);
	//	auto& shader = coordinator.GetComponent<ShaderComponent>(entity);

	//	glGenBuffers(1, &vertices.VBO);
	//	glGenVertexArrays(1, &vertices.VAO);

	//	glBindVertexArray(vertices.VAO);

	//	glBindBuffer(GL_ARRAY_BUFFER, vertices.VBO);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(32), vertices.Vertices, GL_STATIC_DRAW);

	//	glBindVertexArray(vertices.VAO);
	//	//vertices
	//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//	glEnableVertexAttribArray(0);

	//	//normals
	//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//	glEnableVertexAttribArray(1);

	//	//texture
	//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//	glEnableVertexAttribArray(2);

	//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//	glBindVertexArray(0);

	//	coordinator.RemoveComponent<RenderInitializerComponent>(entity);
	//}
}

#endif