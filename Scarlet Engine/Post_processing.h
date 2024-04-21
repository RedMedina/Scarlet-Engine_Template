#ifndef __Post_processing
#define __Post_processing

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Material.h"
#include "TextureLoader.h"
#include "Render.h"
#include "Scene.h"
#include "Scene_Manager.h"
#include "RenderOptions.h"
#include <iostream>

class Post_processing
{
public:
	struct Effects
	{
		bool Bloom = false;
		bool Negative = false;
		bool Grayscale = false;
		bool Blur = false;
		bool SSAO = false;
		float Exposure = 0.5f;
		bool Temperature = false;
		float ColorTemperature = 0.0f;
		bool Saturation = false;
		float SaturationValue = 1.0f;
		bool Vignette = false;
		float Vignette_Radio = 0.3f;
		float Vignette_Smooth= 0.109f;
		float RadiusSSAO = 0.5f;
		int NumSamplesSSAO = 32;
	};

	Effects* effects;
	Post_processing();

	void GetRender();
	void SetRender(Render* render, Scene_Manager* scene);

	Material* mat;
private:
	GLuint quadVAO, quadVBO;
	RenderOptions* renderop;
	GLuint FBOPostProcessMap;
	GLuint ProcessMap;
	GLuint ProcessMap_1;
	GLuint ProcessMapDepth;
	TextureLoader* textureLoader;
};

#endif