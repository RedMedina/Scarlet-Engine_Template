#include "RenderOptions.h"

void RenderOptions::Antialiasing(bool Active)
{
	Active ? glEnable(GL_MULTISAMPLE) : glDisable(GL_MULTISAMPLE);
}

void RenderOptions::ZBuffer(bool Active)
{
	Active ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void RenderOptions::SetDepth(GLenum depthFunc)
{
	glDepthFunc(depthFunc);
}

void RenderOptions::Culling_Face(bool Active)
{
	Active ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
}

void RenderOptions::Face_Mode(GLenum cullFunc)
{
	glCullFace(cullFunc);
}

void RenderOptions::Clean_Scene(glm::vec3 Color)
{
	glClearColor(Color.r, Color.g, Color.b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderOptions::Transparency(bool Active)
{
	if (Active)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}
}