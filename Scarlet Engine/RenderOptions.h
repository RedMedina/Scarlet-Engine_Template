#ifndef __RenderOptions
#define __RenderOptions

#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class RenderOptions
{
public:
	void Antialiasing(bool Active);
	void ZBuffer(bool Active);
	void SetDepth(GLenum depthFunc);
	void Culling_Face(bool Active);
	void Face_Mode(GLenum cullFunc);
	void Clean_Scene(glm::vec3 Color);
	void Transparency(bool Active);
};

#endif