#ifndef RUINUM_SYSTEMS
#define RUINUM_SYSTEMS

#include "../managers/SystemManager.hpp"
#include "../Systems.h";

class RuinumSystems
{
public:
	void Initialize();
	void Execute();
	void CleanUp();

private:
	list<shared_ptr<System>> _systems;
};

void RuinumSystems::Initialize()
{
	_systems.push_back(coordinator.RegisterSystem<RenderInitializeSystem>());
	_systems.push_back(coordinator.RegisterSystem<RenderSystem>());
	_systems.push_back(coordinator.RegisterSystem<CameraSystem>());

	for (shared_ptr<System> system : _systems)
	{
		system->Initialize();
	}
}

void RuinumSystems::Execute() 
{
	for (shared_ptr<System> system : _systems) 
	{
		system->Execute();
	}
}

void RuinumSystems::CleanUp()
{
	for (shared_ptr<System> system : _systems)
	{
		system->CleanUp();
	}
}

#endif