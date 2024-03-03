#ifndef RUINUM_MANAGER
#define RUINUM_MANAGER

#include "Coordinator.hpp"
#include "ComponentRegister.hpp"

#include "systems/RuinumSystems.hpp"

Coordinator coordinator;

class RuinumManager
{
public:
	void Initialize();
	void PostInitialize();
	void Execute();

private:
	RuinumSystems _systems;
	ComponentRegister _register;
};

void RuinumManager::Initialize()
{
	coordinator.Initialize();
	_register.Initialize();
	_systems.Initialize();
}

void RuinumManager::PostInitialize()
{
	_systems.PostInitialize();
}

void RuinumManager::Execute()
{
	_systems.Execute();
	_systems.CleanUp();
}
#endif