#ifndef COMPONENT_ARRAY
#define COMPONENT_ARRAY

#include "ECS.h"

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray: public IComponentArray
{
public:
	void InsertData(Entity entity, T component)
	{
		assert(_entityToMap.find(entity) == _entityToMap.end() && "Component added to same entity more than once.");

		// Put new entry at end and update the maps
		size_t newIndex = mSize;
		_entityToMap[entity] = newIndex;
		_indexToMap[newIndex] = entity;
		_components[newIndex] = component;
		++mSize;
	}

	void RemoveData(Entity entity)
	{
		assert(_entityToMap.find(entity) != _entityToMap.end() && "Removing non-existent component.");

		size_t indexOfRemovedEntity = _entityToMap[entity];
		size_t indexOfLastElement = mSize - 1;
		_components[indexOfRemovedEntity] = _components[indexOfLastElement];

		Entity entityOfLastElement = _indexToMap[indexOfLastElement];
		_entityToMap[entityOfLastElement] = indexOfRemovedEntity;
		_indexToMap[indexOfRemovedEntity] = entityOfLastElement;

		_entityToMap.erase(entity);
		_indexToMap.erase(indexOfLastElement);

		--mSize;
	}

	T& GetData(Entity entity)
	{
		assert(_entityToMap.find(entity) != _entityToMap.end() && "Retrieving non-existent component.");

		return _components[_entityToMap[entity]];
	}

	void EntityDestroyed(Entity entity) override
	{
		if (_entityToMap.find(entity) != _entityToMap.end())
		{
			RemoveData(entity);
		}
	}

private:
	std::array<T, MAX_ENTITIES> _components;
	std::unordered_map<Entity, size_t> _entityToMap; 
	std::unordered_map<size_t, Entity> _indexToMap;
	size_t mSize;
};


#endif