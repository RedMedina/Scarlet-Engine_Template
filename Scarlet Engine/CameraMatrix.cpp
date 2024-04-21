#include "CameraMatrix.h"

glm::mat4 CameraMatrix::ViewMatrix = glm::mat4(1.0f);
glm::mat4 CameraMatrix::ProyectionMatrix = glm::mat4(1.0f);
glm::vec3* CameraMatrix::CameraPosition = NULL;
