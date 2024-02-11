#ifndef CAMERA_COMPONENT
#define CAMERA_COMPONENT

struct CameraComponent
{
	EditorCamera Camera;
	
	CameraComponent(){}
	CameraComponent(EditorCamera& camera) { Camera = camera; }
};

#endif