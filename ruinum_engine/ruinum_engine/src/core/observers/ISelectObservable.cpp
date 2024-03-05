#ifndef ISELECT_OBSERVABLE
#define ISELECT_OBSERVABLE

#include <vector>
#include <iostream>
#include <string>

#include "../ECS.h"
#include "ISelectObserver.cpp"

using namespace std;

class ISelectObservable
{
public:
	void AddSelectObserver(ISelectObserver* observer)
	{
		_observers.push_back(observer);
	}

	void RemoveSelectObserver(ISelectObserver* observer)
	{
		_observers.erase(remove(_observers.begin(), _observers.end(), observer), _observers.end());
	}

	void OnSelectChanged(Entity entity)
	{
		cout << _observers.size();

		for (auto observer : _observers)
		{
			observer->SelectChanged(entity);
		}
	}

protected:
	vector<ISelectObserver*> _observers;
};
#endif