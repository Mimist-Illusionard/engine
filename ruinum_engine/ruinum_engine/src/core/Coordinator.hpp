#ifndef COORDINATOR
#define COORDINATOR

#include "ECS.h"
#include "managers/EntityManager.hpp"
#include "managers/ComponentManager.hpp"
#include "managers/SystemManager.hpp"

#include "../extentions/LogExtentions.h"

#include <memory>

using namespace std;

class Coordinator
{
public:
	void Initialize();
	Entity CreateEntity(const char*);
	void DestroyEntity(Entity);

	template<typename T>
	bool TryGetEntity(Entity& );

	template<typename T>
	void RegisterComponent();

	template<typename T>
	void AddComponent(Entity, T);

	template<typename T>
	void RemoveComponent(Entity);

	template<typename T>
	T& GetComponent(Entity entity);

	template<typename T>
	ComponentType GetComponentType();

	template<typename T>
	std::shared_ptr<T> RegisterSystem();

	template<typename T>
	void SetSystemSignature(Signature signature);

	EntityManager* GetEntityManager()
	{
		return _entityManager.get();
	}

private:
	unique_ptr<ComponentManager> _componentManager;
	unique_ptr<EntityManager> _entityManager;
	unique_ptr<SystemManager> _systemManager;
};

void Coordinator::Initialize()
{
	_componentManager = std::make_unique<ComponentManager>();
	_entityManager = std::make_unique<EntityManager>();
	_systemManager = std::make_unique<SystemManager>();

	_entityManager->AddEntityObserver(_componentManager.get());
	_entityManager->AddEntityObserver(_systemManager.get());
	_entityManager->AddSignatureObserver(_systemManager.get());

	_componentManager->AddComponentObserver(_entityManager.get());
}

Entity Coordinator::CreateEntity(const char* name)
{
	return _entityManager->CreateEntity(name);
}

template<typename T>
bool Coordinator::TryGetEntity(Entity& result)
{
	if (!_entityManager->TryGetEntity<T>(_componentManager->GetComponentType<T>(), result))
	{
		Log("Can't find entity with that component.");
		return false;
	}
	
	return true;
}

void Coordinator::DestroyEntity(Entity entity)
{
	_entityManager->DestroyEntity(entity);
}

template<typename T>
void Coordinator::RegisterComponent()
{
	_componentManager->RegisterComponent<T>();
}

template<typename T>
void Coordinator::AddComponent(Entity entity, T component)
{
	_componentManager->AddComponent<T>(entity, component);
}

template<typename T>
void Coordinator::RemoveComponent(Entity entity)
{
	_componentManager->RemoveComponent<T>(entity);
}

template<typename T>
T& Coordinator::GetComponent(Entity entity)
{
	return _componentManager->GetComponent<T>(entity);
}

template<typename T>
ComponentType Coordinator::GetComponentType()
{
	return _componentManager->GetComponentType<T>();
}

template<typename T>
std::shared_ptr<T> Coordinator::RegisterSystem()
{
	return _systemManager->RegisterSystem<T>();
}

template<typename T>
void Coordinator::SetSystemSignature(Signature signature)
{
	_systemManager->SetSignature<T>(signature);
}

#endif