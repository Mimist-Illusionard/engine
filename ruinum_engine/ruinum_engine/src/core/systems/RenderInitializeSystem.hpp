#ifndef RENDER_INITIALIZE_SYSTEM
#define RENDER_INITIALIZE_SYSTEM

#include <list>

#include "../Components.h"
#include "System.hpp"

void CheckOpenGLError(const char* stmt, const char* fname, int line)
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, stmt);
		abort();
	}
}

#ifdef _DEBUG
#define GL_CHECK(stmt) do { \
            stmt; \
            CheckOpenGLError(#stmt, __FILE__, __LINE__); \
        } while (0)
#else
#define GL_CHECK(stmt) stmt
#endif


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

		GL_CHECK(glGenBuffers(1, &verticesComponent.VBO));
		GL_CHECK(glGenVertexArrays(1, &verticesComponent.VAO));

		GL_CHECK(glBindVertexArray(verticesComponent.VAO));

		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, verticesComponent.VBO));
		GL_CHECK(glBufferData(GL_ARRAY_BUFFER, verticesComponent.Size, verticesComponent.Vertices, GL_STATIC_DRAW));

		GL_CHECK(glBindVertexArray(verticesComponent.VAO));
		
		//vertices
		GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
		GL_CHECK(glEnableVertexAttribArray(0));

		//normals
		GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))));
		GL_CHECK(glEnableVertexAttribArray(1));

		//texture
		GL_CHECK(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))));
		GL_CHECK(glEnableVertexAttribArray(2));
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