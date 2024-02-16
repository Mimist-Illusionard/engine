#ifndef ISIGNATURE_OBSERVABLE
#define ISIGNATURE_OBSERVABLE

#include <vector>
#include <iostream>
#include <string>

#include "../ECS.h"
#include "ISignatureObserver.cpp"

using namespace std;

class ISignatureObservable
{
public:
	void AddSignatureObserver(ISignatureObserver* observer)
	{
		_observers.push_back(observer);
	}

	void RemoveSignatureObserver(ISignatureObserver* observer)
	{
		_observers.erase(remove(_observers.begin(), _observers.end(), observer), _observers.end());
	}

	void OnSignatureChanged(Entity entity, Signature signature)
	{
		for (auto observer : _observers)
		{
			observer->SignatureChanged(entity, signature);
		}
	}

protected:
	vector<ISignatureObserver*> _observers;
};
#endif