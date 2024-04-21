#ifndef __Render
#define __Render

#include <glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <glm/glm.hpp>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Input.h"
#include "Debug.h"
#include "Time.h"
#include "CameraMatrix.h"
#include "MainSettings.h"
#include "Scene.h"
#include <fmod.hpp>
#include <fmod_errors.h>

using namespace std;

class Render
{
private:
	int wScreen = 1300;
	int hScreen = 950;
	GLFWwindow* window;
	float lastFrame = 0.0f;
	string FPS = "";
	string Coord = "";
	FMOD::System* system;
	//FMOD::ChannelGroup* masterGroup;
public:
	bool GameMode = false;

public:
	Render(int w_Screen, int h_Screen, const char* Name_Screen, int WindowPosX, int WindowPosY);
	void Draw(Scene* RenderScene);
	void Update(Scene* RenderScene);
	~Render();
};

#endif