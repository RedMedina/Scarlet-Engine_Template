#include "MainLightData.h"

glm::vec3* MainLightData::MainLightPos = NULL;
glm::vec3* MainLightData::MainLightColor = NULL;
glm::vec3* MainLightData::MainLightSpecular = NULL;
glm::vec3* MainLightData::MainLightDiffuse = NULL;
std::vector<Point_Light*> MainLightData::Point_Lights = std::vector<Point_Light*>();
float MainLightData::SHADOW_HEIGHT = 1024; //1024
float MainLightData::SHADOW_WIDTH = 1024;
float MainLightData::near_plane = 1.0f;
float MainLightData::far_plane = 2000.0f; //7.5f
bool MainLightData::DIRECTIONAL_LIGHT_SHADOWMAP = true;
glm::mat4 MainLightData::lightSpaceMatrix = glm::mat4(1.0f);
glm::mat4 MainLightData::lightProjection = glm::mat4(1.0f);
glm::mat4 MainLightData::lightView = glm::mat4(1.0f);
unsigned int* MainLightData::DEPTHMAP = NULL;
unsigned int* MainLightData::POSTMAP = NULL;
unsigned int* MainLightData::POSTMAP_1 = NULL;
unsigned int* MainLightData::POSTMAP_DEPTH = NULL;
unsigned int* MainLightData::FRAMEBUFFERPOST = NULL;
