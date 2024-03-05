#ifndef TRANSFORM_COMPONENT_DRAWER
#define TRANSFORM_COMPONENT_DRAWER

#include "ComponentDrawer.hpp"

class TransformComponentDrawer: public ComponentDrawer
{
public:
	void Set(Entity);
	void Draw();

private:
	TransformComponent* _component;
};

void TransformComponentDrawer::Set(Entity entity)
{
	std::cout << "test";
	_component = &coordinator.GetComponent<TransformComponent>(entity);
}

void TransformComponentDrawer::Draw()
{
	cout << "Draw TransfomComponent";

	Text("Transform Component");
	
	Text("Position:");
	DragFloat("x", &_component->Position.x, 0.05f);
	DragFloat("y", &_component->Position.y, 0.05f);
	DragFloat("z", &_component->Position.z, 0.05f);
	
	Text("Scale:");
	DragFloat("x", &_component->Scale.x, 0.05f);
	DragFloat("y", &_component->Scale.y, 0.05f);
	DragFloat("z", &_component->Scale.z, 0.05f);

	Text("Angle");
	DragFloat("", &_component->Angle, 0.05f);
}

#endif