#ifndef CAMERA_SYSTEM
#define CAMERA_SYSTEM

#include "System.hpp"

class CameraSystem: public System
{
public:
	void Initialize();
	void Execute();

private:
	 
};

void CameraSystem::Initialize()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<CameraComponent>());
	coordinator.SetSystemSignature<CameraSystem>(signature);
}

void CameraSystem::Execute()
{	
}

#endif