#ifndef __AnimatedModel
#define __AnimatedModel

#include "Component.h"
#include "CameraMatrix.h"
#include "glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Material.h"
#include "MainLightData.h"
#include "Point_Light.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ModelAnim.h"
#include "Animator.h"

class AnimatedModel : public Component
{
public:
	glm::vec3* position;
	glm::vec3* rotation;
	glm::vec3* scale;
	RenderOptions* settings;
	Material* mat;
	bool GetPointLights = true;
	bool HDRColor = false;
	float exposure = 1.0f;
	AnimatedModel(const char* modelpath, Material* m, glm::vec3* pos, glm::vec3* rot, glm::vec3* sca);
	void SetupAnimator();
	void Update() override;
	void Draw() override;
	void SetMaterial(Material* m);

	Model* model;
	Animator* animator;
	std::vector<Animation*> animations;
};

#endif