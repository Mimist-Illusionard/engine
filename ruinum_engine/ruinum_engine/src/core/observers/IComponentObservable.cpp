#ifndef ICOMPONENT_OBSERVABLE
#define ICOMPONENT_OBSERVABLE

#include <vector>
#include <iostream>
#include <string>

#include "../ECS.h"
#include "IComponentObserver.cpp"

using namespace std;

class IComponentObservable
{
public:
	void AddComponentObserver(IComponentObserver* observer)
	{
		_observers.push_back(observer);
	}

	void RemoveComponentObserver(IComponentObserver* observer)
	{
		_observers.erase(remove(_observers.begin(), _observers.end(), observer), _observers.end());
	}

	void OnComponentAdded(Entity entity, ComponentType componentType)
	{
		for (auto observer : _observers)
		{
			observer->ComponentAdded(entity, componentType);
		}
	}

	void OnComponentRemoved(Entity entity, ComponentType componentType)
	{
		for (auto observer : _observers)
		{
			observer->ComponentRemoved(entity, componentType);
		}
	}

protected:
	vector<IComponentObserver*> _observers;
};
#endif