#ifndef IENTITY_OBSERVABLE
#define IENTITY_OBSERVABLE

#include <vector>
#include <iostream>
#include <string>

#include "../ECS.h"
#include "IEntityObserver.cpp"

using namespace std;

class IEntityObservable
{
public:
	void AddObserver(IEntityObserver* observer)
	{
		_observers.push_back(observer);
	}

	void RemoveObserver(IEntityObserver* observer)
	{
		_observers.erase(remove(_observers.begin(), _observers.end(), observer), _observers.end());
	}

	void OnEntityCreated(Entity entity, const char* name)
	{
		for (auto observer : _observers)
		{
			observer->EntityCreated(entity, name);
		}
	}

	void OnEntityDestroyed(Entity entity)
	{
		for (auto observer : _observers)
		{
			observer->EntityDestroyed(entity);
		}
	}

protected:
	vector<IEntityObserver*> _observers;
};
#endif