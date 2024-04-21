#ifndef __Billboard
#define __Billboard

#include "Component.h"
#include "CameraMatrix.h"
#include "glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Material.h"
#include "MainLightData.h"
#include "Point_Light.h"

class Billboard : public Component
{
public:
	Billboard(glm::vec3* pos, glm::vec3* sca);
	~Billboard();
	void Update() override;
	void Draw() override;
	void SetMaterial(Material* m);

	glm::vec3* position;
	glm::vec3* scale;
	RenderOptions* settings;
	bool GetPointLights = true;

private:
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	Material* mat;
};

#endif