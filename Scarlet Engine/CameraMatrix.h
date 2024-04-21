#ifndef __CameraMatrix
#define __CameraMatrix

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

static class CameraMatrix
{
public:
	static glm::mat4 ViewMatrix;
	static glm::mat4 ProyectionMatrix;
	static glm::vec3* CameraPosition;
};

#endif