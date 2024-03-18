#ifndef ENTITY_EXTENTIONS
#define ENTITY_EXTENTIONS

#include "../src/core/RuinumManager.hpp"

extern Coordinator coordinator;

template<typename T>
bool HasComponent(Entity entity)
{
	Signature signature = coordinator.GetEntityManager()->GetSignature(entity);

	if (signature.test(coordinator.GetComponentType<T>()))
	{
		return true;
	}

	return false;
}

#endif