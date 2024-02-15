#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

#include <queue>
#include <list>
#include <array>
#include <cassert>
#include <iostream>

#include "../ECS.h"
#include "../RuinumManager.hpp"
#include "../observers/IEntityObservable.cpp"

using namespace std;

class EntityManager : public IEntityObservable
{
public:
	EntityManager();

	Entity CreateEntity(const char*);
	void DestroyEntity(Entity);
	void SetSignature(Entity, Signature);
	Signature GetSignature(Entity entity);
	
	template<typename T>
	bool TryGetEntity(ComponentType, Entity&);

private:
	queue<Entity> _freeEntities;
	list<Entity> _entities;
	array<Signature, MAX_ENTITIES> _signatures;
	uint32_t _entityAmount = 0;
};

EntityManager::EntityManager()
{
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
	{
		_freeEntities.push(entity);
	}
}

Entity EntityManager::CreateEntity(const char* name)
{
	assert(_entityAmount < MAX_ENTITIES && "Too many entities exits.");

	Entity entity = _freeEntities.front();
	_freeEntities.pop();

	_entities.push_back(entity);

	++_entityAmount;

	OnEntityCreated(entity, name);

	return entity;
}

void EntityManager::DestroyEntity(Entity entity) 
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	_signatures[entity].reset();
	_freeEntities.push(entity);
	_entities.erase(remove(_entities.begin(), _entities.end(), entity), _entities.end());

	OnEntityDestroyed(entity);
	--_entityAmount;
}

void EntityManager::SetSignature(Entity entity, Signature signature)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	_signatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity)
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	return _signatures[entity];
}

template<typename T>
bool EntityManager::TryGetEntity(ComponentType componentType, Entity& result)
{
	for (Entity entity : _entities)
	{
		Signature signature = GetSignature(entity);

		if (signature.test(componentType)) 
		{ 
			result = entity;
			return true;
		}
	}

	return false;
}

#endif