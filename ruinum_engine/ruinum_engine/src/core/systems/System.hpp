#ifndef SYSTEM
#define SYSTEM

#include "../ECS.h"
#include "../Components.h"
#include "../Coordinator.hpp"

#include <set>

class System
{
public:
	virtual void Initialize() {}
	virtual void Execute() {}
	virtual void OnDestroy() {}

	std::set<Entity> Entities;

private:
};

#endif