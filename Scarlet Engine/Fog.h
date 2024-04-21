#ifndef __Fog
#define __Fog

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "MainSettings.h"

class Fog
{
public:
	float startFog = 0.1f;
	float endFog = 5.0f;
	float fogDensity = 0.1f;;
	GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLenum FogMode;
	
	//GL_LINEAR
	//GL_EXP exponencial
	//GL_EXP2 exponencial quadratic

	Fog(GLenum FOGMODE)
	{
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, FOGMODE);
		glFogfv(GL_FOG_COLOR, fogColor);

		FogMode = FOGMODE;

		if(FOGMODE == GL_LINEAR)
		{	
			glFogf(GL_FOG_START, startFog);
			glFogf(GL_FOG_END, endFog);
		}
		else
		{
			glFogf(GL_FOG_DENSITY, fogDensity);
		}
	}

	void Render()
	{
		if(MainSettings::RenderN == MainSettings::NumRenders)
		{
			ImGui::SliderFloat("Fog Density", &fogDensity, 0.0f, 80.0f);
			ImGui::SliderFloat("Fog Start", &startFog, 0.0f, 80.0f);
			ImGui::SliderFloat("Fog End", &endFog, 0.0f, 80.0f);
			ImGui::ColorPicker3("Fog Color", fogColor);
		}

		glEnable(GL_FOG);

		if (FogMode == GL_LINEAR)
		{
			glFogi(GL_FOG_MODE, GL_LINEAR);
			glFogf(GL_FOG_START, startFog);
			glFogf(GL_FOG_END, endFog);
			glFogfv(GL_FOG_COLOR, fogColor);
		}
		else if(FogMode == GL_EXP)
		{
			glFogi(GL_FOG_MODE, GL_EXP);
			glFogf(GL_FOG_DENSITY, fogDensity);
			glFogfv(GL_FOG_COLOR, fogColor);
		}
		else
		{
			glFogi(GL_FOG_MODE, GL_EXP2);
			glFogf(GL_FOG_DENSITY, fogDensity);
			glFogfv(GL_FOG_COLOR, fogColor);
		}
	}

	void EndFog()
	{
		glDisable(GL_FOG);
	}
};

#endif