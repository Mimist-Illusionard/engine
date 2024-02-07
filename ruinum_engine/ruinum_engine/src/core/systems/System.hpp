#ifndef SYSTEM
#define SYSTEM

#include "../ECS.h"
#include <set>

class System
{
public:
	std::set<Entity> _entities;
};

#endif