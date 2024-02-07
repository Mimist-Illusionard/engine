#ifndef COMPONENT_MANAGER
#define COMPONENT_MANAGER

#include "../ECS.h"
#include "../ComponentArray.hpp"

#include <any>
#include <memory>
#include <unordered_map>

using namespace std;

class ComponentManager
{
public:
	template<typename T>
	void RegisterComponent();
	
	template<typename T>
	ComponentType GetComponentType();

	template<typename T>
	void AddComponent();

	template<typename T>
	void RemoveComponent();

	template<typename T>
	T& GetComponent();

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
	const char* typeName = typeid(T).name;
	assert(_componentTypes.find(typeName) == _componentTypes.end() && "Component alredy registered.");

	_componentTypes.insert({ typeName, _componentTypeId });
	_components.insert({ typeName, make_shared<ComponentArray<T>>() });

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
void ComponentManager::AddComponent()
{
	GetComponentArray<T>()->InsertData(entity, component);
}

template<typename T>
void ComponentManager::RemoveComponent()
{
	GetComponentArray<T>()->RemoveData(entity);
}

template<typename T>
T& ComponentManager::GetComponent()
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
