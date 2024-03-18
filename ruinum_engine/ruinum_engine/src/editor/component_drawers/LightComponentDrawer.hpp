#ifndef LIGHT_COMPONENT_DRAWER
#define LIGHT_COMPONENT_DRAWER

#include "ComponentDrawer.hpp"

class LightComponentDrawer : public ComponentDrawer
{
public:
	void Set(Entity);
	void Draw();

private:
	LightComponent* _component;
};

void LightComponentDrawer::Set(Entity entity)
{
	_component = &coordinator.GetComponent<LightComponent>(entity);
}

void LightComponentDrawer::Draw()
{
	if (ImGui::CollapsingHeader("Light Component", ImGuiTreeNodeFlags_None))
	{
		Text("Color:");
		DragFloat("red", &_component->Color.x, 0.05f);
		DragFloat("green", &_component->Color.y, 0.05f);
		DragFloat("blue", &_component->Color.z, 0.05f);

		Text("Ambient:");
		DragFloat("x_ambient", &_component->Ambient.x, 0.05f);
		DragFloat("y_ambient", &_component->Ambient.y, 0.05f);
		DragFloat("z_ambient", &_component->Ambient.z, 0.05f);

		Text("Diffuse:");
		DragFloat("x_diffuse", &_component->Diffuse.x, 0.05f);
		DragFloat("y_diffuse", &_component->Diffuse.y, 0.05f);
		DragFloat("z_diffuse", &_component->Diffuse.z, 0.05f);

		Text("Specular:");
		DragFloat("x_specular", &_component->Specular.x, 0.05f);
		DragFloat("y_specular", &_component->Specular.y, 0.05f);
		DragFloat("z_specular", &_component->Specular.z, 0.05f);
	}
}
#endif