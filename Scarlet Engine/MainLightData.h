#ifndef __MainLightData
#define __MainLightData


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


class Point_Light;

static class MainLightData
{
public:
	static glm::vec3* MainLightPos;
	static glm::vec3* MainLightColor;
	static glm::vec3* MainLightSpecular;
	static glm::vec3* MainLightDiffuse;
	static std::vector<Point_Light*> Point_Lights;
	static float SHADOW_WIDTH;
	static float SHADOW_HEIGHT;
	static bool DIRECTIONAL_LIGHT_SHADOWMAP;
	static float near_plane;
	static float far_plane;
	static glm::mat4 lightSpaceMatrix;
	static glm::mat4 lightProjection;
	static glm::mat4 lightView;
	static unsigned int* DEPTHMAP;
	static unsigned int* POSTMAP;
	static unsigned int* POSTMAP_1;
	static unsigned int* POSTMAP_DEPTH;
	static unsigned int* FRAMEBUFFERPOST;
};

#endif