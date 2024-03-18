#ifndef MATERIAL_COMPONENT_DRAWER
#define MATERIAL_COMPONENT_DRAWER

#include "ComponentDrawer.hpp"

class MaterialComponentDrawer : public ComponentDrawer
{
public:
	void Set(Entity);
	void Draw();

private:
	MaterialComponent* _component;
};

void MaterialComponentDrawer::Set(Entity entity)
{
	_component = &coordinator.GetComponent<MaterialComponent>(entity);
}

void MaterialComponentDrawer::Draw()
{
	if (ImGui::CollapsingHeader("Material Component", ImGuiTreeNodeFlags_None))
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

		Text("Shininess");
		DragFloat("s", &_component->Shininess, 0.05f);
	}
}
#endif