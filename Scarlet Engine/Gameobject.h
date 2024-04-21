#ifndef __GameObject
#define __GameObject

#include <vector>
#include <string>
#include "Transform.h"
#include "Component.h"
#include "MainSettings.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

class GameObject
{
public:
	std::vector<Component*> components;
	std::vector<GameObject*> children;
	const char* name;

	GameObject(const char* name_gm);
	void Update();
	void Draw();
};

#endif