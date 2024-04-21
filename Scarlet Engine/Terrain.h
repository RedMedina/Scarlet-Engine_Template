#ifndef __Terrain
#define __Terrain

#include "Component.h"
#include "CameraMatrix.h"
#include "MainLightData.h"
#include "glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Material.h"
#include "MainLightData.h"
#include "Point_Light.h"
#include "TextureLoader.h"

class Terrain : public Component
{
public:
	Terrain(const char* heightmap);
	~Terrain();
	void Update() override;
	void Draw() override;
	void SetMaterial(Material* m);

	glm::vec3* position;
	bool GetPointLights = true;
	RenderOptions* settings;

private:
	void CalculateNormals();

	GLuint VertexArrayID;
	std::vector<float> vertices;
	std::vector<unsigned> indexes;
	std::vector<glm::vec3> normals;
	std::vector<float> uvs;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint indexbuffer;
	GLuint normalbuffer;
	Material* mat;
	int NStrips;
	int NTrisPerStrip;
};

#endif