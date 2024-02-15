#ifndef IENTITY_OBSERVER
#define IENTITY_OBSERVER

#include "../ECS.h"

class IEntityObserver
{
public:
	virtual void EntityCreated(Entity entity, const char* name) {};
	virtual void EntityDestroyed(Entity entity) {};
};

#endif
