#ifndef ISELECT_OBSERVER
#define ISELECT_OBSERVER

#include "../ECS.h"

class ISelectObserver
{
public:
	virtual void SelectChanged(Entity entity) {}
};

#endif