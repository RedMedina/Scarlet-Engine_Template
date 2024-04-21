#ifndef __Animator
#define __Animator

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
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include "bone.h"
#include "Animation.h"
#include "Time.h"

class Animator : public Component
{
public:
	std::vector<Animation*> animations;

	Animator(std::vector<Animation*> anims);
	void Update() override;
	void Draw() override;
	void PlayAnimation(int index_Animation);
	std::vector<glm::mat4> GetFinalBoneMatrices();

private:
	void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);
	Animation* m_CurrentAnimation;
	std::vector<glm::mat4> m_FinalBoneMatrices;
	float m_CurrentTime;
};

#endif