#ifndef __AudioSource
#define __AudioSource

#include "Component.h"
#include "MainSettings.h"
#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

class AudioSource : public Component
{
public:
	AudioSource(const char* soundpath, glm::vec3 Position, bool is3D);
	void Update() override;
	void Draw() override;
	void play();
	void stop();
	void pause();
	void SetLoop();
	void NoLoop();
	void SetMusicSpeed(float speed);
	void setVolume(float volume);
	~AudioSource();

	bool is3DSound;
	FMOD::System* m_system;
	FMOD::Sound* m_sound;
	FMOD::Channel* m_channel;
	
private:
	bool PlayBTN = true;
	bool PlauseBTN = false;
	bool LoopBTN = false;
	float volumeF = 1.0f;
	float speedF = 1.0f;
};

#endif