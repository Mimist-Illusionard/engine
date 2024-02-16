#ifndef COMPONENT_MANAGER
#define COMPONENT_MANAGER

#include "../ECS.h"
#include "../ComponentArray.hpp"
#include "../observers/IComponentObservable.cpp"

#include <any>
#include <memory>
#include <unordered_map>

using namespace std;

class ComponentManager: public IComponentObservable, public IEntityObserver
{
public:
	template<typename T>
	void RegisterComponent();
	
	template<typename T>
	ComponentType GetComponentType();

	template<typename T>
	void AddComponent(Entity, T component);

	template<typename T>
	void RemoveComponent(Entity);

	template<typename T>
	T& GetComponent(Entity);

	void EntityDestroyed(Entity);

private:
	unordered_map<const char*, ComponentType> _componentTypes{};
	unordered_map<const char*, std::shared_ptr<IComponentArray>> _components{};
	ComponentType _componentTypeId = 0;

	template<typename T>
	shared_ptr<ComponentArray<T>> GetComponentArray();	
};

template<typename T>
void ComponentManager::RegisterComponent()
{
	const char* typeName = typeid(T).name();

	assert(_componentTypes.find(typeName) == _componentTypes.end() && "Registering component type more than once.");

	_componentTypes.insert({ typeName, _componentTypeId });
	_components.insert({ typeName, std::make_shared<ComponentArray<T>>() });

	++_componentTypeId;
}

template<typename T>
ComponentType ComponentManager::GetComponentType()
{
	const char* typeName = typeid(T).name();

	assert(_componentTypes.find(typeName) != _componentTypes.end() && "Component not registered before use.");

	return _componentTypes[typeName];
}

template<typename T>
void ComponentManager::AddComponent(Entity entity, T component)
{
	GetComponentArray<T>()->InsertData(entity, component);
	OnComponentAdded(entity, GetComponentType<T>());
}

template<typename T>
void ComponentManager::RemoveComponent(Entity entity)
{
	GetComponentArray<T>()->RemoveData(entity);
	OnComponentRemoved(entity, GetComponentType<T>());
}

template<typename T>
T& ComponentManager::GetComponent(Entity entity)
{
	return GetComponentArray<T>()->GetData(entity);
}

void ComponentManager::EntityDestroyed(Entity entity)
{
	for (auto const& pair : _components)
	{
		auto const& component = pair.second;

		component->EntityDestroyed(entity);
	}
}

template<typename T>
shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray()
{
	const char* typeName = typeid(T).name();

	assert(_componentTypes.find(typeName) != _componentTypes.end() && "Component not registered before use.");

	return std::static_pointer_cast<ComponentArray<T>>(_components[typeName]);
}

#endif
