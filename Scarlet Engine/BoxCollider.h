#ifndef __BoxCollider
#define __BoxCollider

#include "Component.h"
#include "Material.h"
#include "CameraMatrix.h"
#include "MainSettings.h"
#include "glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

class BoxCollider : public Component
{
public:
	BoxCollider(glm::vec3* Position, glm::vec3* Rotation, glm::vec3* Size);
	void Update() override;
	void Draw() override;
	bool intersectBox(BoxCollider* box1, BoxCollider* box2);

	glm::vec3* offsetPos = new glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3* offsetScale = new glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec4* boxColor = new glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	bool* show = new bool(true);
	Material* mat;
	glm::vec3* rotation;

private:
	glm::vec3* pos;
	glm::vec3* scale;
	std::vector<glm::vec3> vertices;
	GLuint VertexArrayID, vertexbuffer;
};

#endif