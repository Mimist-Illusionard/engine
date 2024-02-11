#ifndef SYSTEM_MANAGER
#define SYSTEM_MANAGER

#include "../ECS.h"
#include "../systems/System.hpp"

#include <cassert>
#include <memory>
#include <unordered_map>

using namespace std;

class SystemManager
{
public:

	template<typename T>
	shared_ptr<T> RegisterSystem();

	template<typename T>
	void SetSignature(Signature);

	void EntityDestroyed(Entity);
	void EntitySignatureChanged(Entity, Signature);

private:
	unordered_map<const char*, Signature> _signatures{};
	unordered_map<const char*, std::shared_ptr<System>> _systems{};
};

template<typename T>
shared_ptr<T> SystemManager::RegisterSystem()
{
	const char* typeName = typeid(T).name();

	assert(_systems.find(typeName) == _systems.end() && "Registering system more than once.");

	auto system = std::make_shared<T>();
	_systems.insert({ typeName, system });
	return system;
}

template<typename T>
void SystemManager::SetSignature(Signature signature)
{
	const char* typeName = typeid(T).name();

	assert(_systems.find(typeName) != _systems.end() && "System used before registered.");

	_signatures.insert({ typeName, signature });
}


void SystemManager::EntityDestroyed(Entity entity)
{
	for (auto const& pair : _systems)
	{
		auto const& system = pair.second;
		system->Entities.erase(entity);
	}
}

void SystemManager::EntitySignatureChanged(Entity entity, Signature signature)
{
	for (auto const& pair : _systems)
	{
		auto const& type = pair.first;
		auto const& system = pair.second;
		auto const& systemSignature = _signatures[type];

		//cout << type << " " << endl;
		//cout << systemSignature << " " << signature << endl;
		//cout << "-------" << endl;

		if ((signature & systemSignature) == systemSignature)
		{
			system->Entities.insert(entity);
		}
		else
		{
			system->Entities.erase(entity);
		}
	}
}
#endif