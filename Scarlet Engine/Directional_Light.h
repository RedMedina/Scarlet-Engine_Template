#ifndef __DirectionalLight
#define __DirectionalLight

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "MainLightData.h"
#include "CameraMatrix.h"
#include "Component.h"
#include "Input.h"
#include "Time.h"
#include "MainSettings.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

class Directional_Light : public Component
{
public:
	Directional_Light(glm::vec3* Direction, glm::vec3* AmbientColor, glm::vec3* DiffuseColor, glm::vec3* SpecularColor, bool mainLight);

	void Update() override;
	void Draw() override;

	glm::vec3* Direction;
	glm::vec3* AmbientColor;
	glm::vec3* DiffuseColor;
	glm::vec3* SpecularColor;
	bool isMainLight = false;
	bool EmitShadow = true;
};

#endif