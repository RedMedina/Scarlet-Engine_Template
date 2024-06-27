#ifndef __MeshRenderer
#define __MeshRenderer

#include "Component.h"
#include "CameraMatrix.h"
#include "StaticMeshLoader.h"
#include "glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Material.h"
#include "MainLightData.h"
#include "Point_Light.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

class MeshRenderer : public Component
{
public:
	glm::vec3* position;
	glm::vec3* rotation;
	glm::vec3* scale;
	RenderOptions* settings;
	bool GetPointLights = true;
	bool HDRColor = false;
	float exposure = 1.0f;
	glm::vec3 EmissionColor = glm::vec3(1.0f, 1.0f, 1.0f);
	int UINum = 0;

	MeshRenderer(const char* modelpath, glm::vec3* pos, glm::vec3* rot, glm::vec3* sca);
	void SetMaterial(Material* m);
	Material* GetMaterial();
	void Update() override;
	void Draw() override;

private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint VertexArrayID;
	StaticMeshLoader* ModelLoader;
	Material* mat;
};

#endif