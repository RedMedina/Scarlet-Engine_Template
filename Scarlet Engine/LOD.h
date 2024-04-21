#ifndef __Lod
#define __Lod

#include "Component.h"
#include "CameraMatrix.h"
#include "Gameobject.h"
#include "glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

class LOD : public Component
{
public:
	struct LodItem
	{
		GameObject* objLod = NULL;
		float MAX_RENDER_distance = 0;
	};
	std::vector<LodItem> LOD_Levels;
	glm::vec3* position;
	glm::vec3* rotation;
	glm::vec3* scale;
	LOD(glm::vec3* pos, glm::vec3* rot, glm::vec3* sca);
	float CalcDistance();
	void Update() override;
	void Draw() override;
};

#endif