#ifndef __PointLight
#define __PointLight

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "MainLightData.h"
#include "Component.h"
#include "MainSettings.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

class Point_Light : public Component
{
public:
	Point_Light(glm::vec3* Position, glm::vec3* AmbientColor, glm::vec3* DiffuseColor, glm::vec3* SpecularColor, float Constant, float Linear, float Cuadratic, bool mainLight);

	void Update() override;
	void Draw() override;

	glm::vec3* Position;
	glm::vec3* AmbientColor;
	glm::vec3* DiffuseColor;
	glm::vec3* SpecularColor;
	float Constant;
	float Linear;
	float Cuadratic;

	bool isMainLight = false;
};

#endif
