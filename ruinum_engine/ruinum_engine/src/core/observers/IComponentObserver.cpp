#ifndef ICOMPONENT_OBSERVER
#define ICOMPONENT_OBSERVER

#include "../ECS.h"

class IComponentObserver
{
public:
	virtual void ComponentAdded(Entity entity, ComponentType componentType) {}
	virtual void ComponentRemoved(Entity entity, ComponentType componentType) {}
};

#endif
