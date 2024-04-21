#ifndef __Scene
#define __Scene

#include <vector>
#include "Gameobject.h"
#include "RenderOptions.h"
#include "LightOptions.h"
#include "MainLightData.h"
#include "MainSettings.h"
#include "CameraMatrix.h"
#include "Camera.h"
#include "TextureLoader.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include <iostream>
#include "Fog.h"

class Scene
{
private:
	
	LightOptions* Light_Settings;
	Material* Skybox_Material;
	//Fog* Niebla;

public:
	std::vector<GameObject*> GameObjects;
	RenderOptions* Render_Settings;
	GLuint FBOShadowMap;
	GLuint DepthMap;
	TextureLoader* textureLoader;

	void Start()
	{
		//Configuración de la escena;
		Render_Settings = new RenderOptions;

		//Configuración básica
		Render_Settings->Antialiasing(true);
		Render_Settings->ZBuffer(true);
		Render_Settings->SetDepth(GL_LESS);
		Render_Settings->Culling_Face(true);
		Render_Settings->Face_Mode(GL_BACK);

		Light_Settings = new LightOptions;
		Light_Settings->Create_Skybox();
		Skybox_Material = new Material("skybox.vs", "skybox.ps");
		Skybox_Material->Material_Settings->Z_Equal = true;
		//Skybox_Material->Material_Settings->Transparent = true;
		Light_Settings->Set_Skybox_Material(Skybox_Material);

		//Niebla
		//Niebla = new Fog(GL_EXP);
		//Niebla->startFog = 10.0f;
		//Niebla->endFog = 50.0f;

		//Shadow Map
		textureLoader = new TextureLoader;

		FBOShadowMap = textureLoader->FrameDepthBuffer();
		DepthMap = textureLoader->DepthMap(MainLightData::SHADOW_WIDTH, MainLightData::SHADOW_HEIGHT, FBOShadowMap);
		MainLightData::DEPTHMAP = &DepthMap;
		
		std::cout << "SHADOW MAP DEPTH MAP: " << *MainLightData::DEPTHMAP << endl;
		std::cout << "SHADOW MAP FBO: " << FBOShadowMap << endl;
	}

	void Update()
	{
		for (GameObject* Obj : GameObjects) {
			Obj->Update();
		}

		Light_Settings->Update_Skybox();
	}

	void Draw(float deltaTime)
	{
		ImGui::Begin("Scarlet Engine: Hierarchy");

		Render_Settings->Clean_Scene(glm::vec3(0.0f, 0.0f, 0.0f));

		//Render Num = 1
		MainSettings::RenderN++;

		//First Render for shadowmap
		// Ten en cuenta que si usas una matriz de proyección en perspectiva tendrás que cambiar la posición de la luz ya que la posición de la luz actual no es suficiente para reflejar toda la escena
		MainLightData::lightProjection = glm::perspective(glm::radians(45.0f), MainLightData::SHADOW_WIDTH / MainLightData::SHADOW_HEIGHT, 15.0f, MainLightData::far_plane);
		//MainLightData::lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, MainLightData::near_plane, 7.5f);
		MainLightData::lightView = glm::lookAt(*MainLightData::MainLightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));

		CameraMatrix::ProyectionMatrix = MainLightData::lightProjection;
		CameraMatrix::ViewMatrix = MainLightData::lightView;
		MainLightData::lightSpaceMatrix = MainLightData::lightProjection * MainLightData::lightView;
		
		dynamic_cast<Camera*>(GameObjects[0]->components[1])->MainCamera = false;
		CameraMatrix::CameraPosition = dynamic_cast<Camera*>(GameObjects[0]->components[1])->Position;

		glViewport(0, 0, MainLightData::SHADOW_WIDTH, MainLightData::SHADOW_HEIGHT);
		textureLoader->Bind_DepthFrameBuffer(FBOShadowMap);

		Skybox_Material->Set_Config(Render_Settings);
		Skybox_Material->Draw();
		Skybox_Material->SetValue("Color", glm::vec3(0.0f, 0.0f, 1.0f));
		Skybox_Material->SetValue("light_direction", *MainLightData::MainLightPos);
		Skybox_Material->SetValue("light_color", *MainLightData::MainLightColor);
		Light_Settings->Draw_Skybox();
		Skybox_Material->End_Config(Render_Settings);

		for (GameObject* Obj : GameObjects) {
			Obj->Draw();
		}

		textureLoader->Unbind_FrameBuffer();

		//Second Render shadowmap processed

		Render_Settings->Clean_Scene(glm::vec3(0.0f, 0.0f, 0.0f));
		glViewport(0, 0, MainSettings::w_window, MainSettings::h_window);
		
		textureLoader->Bind_FrameBuffer(*MainLightData::FRAMEBUFFERPOST);

		//Render Num = 2
		MainSettings::RenderN++;

		dynamic_cast<Camera*>(GameObjects[0]->components[1])->MainCamera = true;

		Skybox_Material->Set_Config(Render_Settings);
		Skybox_Material->Draw();
		Skybox_Material->SetValue("Color", glm::vec3(0.0f, 0.0f, 1.0f));
		Skybox_Material->SetValue("light_direction", *MainLightData::MainLightPos);
		Skybox_Material->SetValue("light_color", *MainLightData::MainLightColor);
		Light_Settings->Draw_Skybox();
		Skybox_Material->End_Config(Render_Settings);

		for (GameObject* Obj : GameObjects) {
			Obj->Draw();
		}

		textureLoader->Unbind_FrameBuffer();

		//Tercer Render Postprocesado y Framebuffer Render

		Render_Settings->Clean_Scene(glm::vec3(0.0f, 0.0f, 0.0f));
		glViewport(0, 0, MainSettings::w_window, MainSettings::h_window);

		//Render Num = 3
		MainSettings::RenderN++;

		dynamic_cast<Camera*>(GameObjects[0]->components[1])->MainCamera = true;

		Skybox_Material->Set_Config(Render_Settings);
		Skybox_Material->Draw();
		Skybox_Material->SetValue("Color", glm::vec3(0.0f, 0.0f, 1.0f));
		Skybox_Material->SetValue("light_direction", *MainLightData::MainLightPos);
		Skybox_Material->SetValue("light_color", *MainLightData::MainLightColor);
		Light_Settings->Draw_Skybox();
		Skybox_Material->End_Config(Render_Settings);

		for (GameObject* Obj : GameObjects) {
			Obj->Draw();
		}

		if(MainSettings::render_ui)
		{
			if (ImGui::Button("Save"))
				cout << "Scene Saved." << endl;
		}

		ImGui::End();
		
	}

	~Scene()
	{
		for (GameObject* obj : GameObjects) {
			delete obj;
		}
		GameObjects.clear();
		delete Render_Settings;
		delete Light_Settings;
		delete Skybox_Material;
	}
};

#endif