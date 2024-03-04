#ifndef COMPONENT_DRAWER
#define COMPONENT_DRAWER

#include "../../core/ECS.h"
#include "../../core/Components.h"
#include "../../core/RuinumManager.hpp"

#include "imgui/imgui.h"

using namespace ImGui;

class ComponentDrawer
{
public:
	virtual void Set(Entity) {}
	virtual void Draw() { cout << "test"; }
};

#endif