#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

#include <queue>
#include <array>
#include <cassert>

#include "../ECS.h"

using namespace std;

class EntityManager
{
public:
	EntityManager();

	Entity CreateEntity();
	void DestroyEntity(Entity);
	void SetSignature(Entity, Signature);
	Signature GetSignature(Entity entity);

private:
	queue<Entity> _entities;
	array<Signature, MAX_ENTITIES> _signatures;
	uint32_t _entityAmount = 0;
};

EntityManager::EntityManager()
{
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
	{
		_entities.push(entity);
	}
}

Entity EntityManager::CreateEntity()
{
	assert(_entityAmount < MAX_ENTITIES && "Too many entities in existence.");

	Entity id = _entities.front();
	_entities.pop();
	++_entityAmount;

	return id;
}

void EntityManager::DestroyEntity(Entity entity) 
{
	assert(entity < MAX_ENTITIES && "Entity out of range.");

	_signatures[entity].reset();
	_entities.push(entity);
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

#endif