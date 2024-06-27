#ifndef __WaterEffect
#define __WaterEffect

#include "Component.h"
#include "CameraMatrix.h"
#include <glm/glm.hpp>
#include "Material.h"
#include "Time.h"

class WaterEffect : public Component
{
public:
	Material* WaterMaterial;
	float TimeWaves = 0.0f;
	
	//Start
	WaterEffect()
	{
		TimeWaves = 0.0f;
	}

	//Update
	void Update() override
	{
		TimeWaves += 0.0005f;
	}

	void Draw() override
	{
		WaterMaterial->SetVec3("SpecularColor", glm::vec3(1.0f, 1.0f, 1.0f));
		WaterMaterial->SetVec4("ColorTexture", glm::vec4(0.5f, 0.8f, 1.0f, 1.0f));
		//WaterMaterial->SetMat4("p", CameraMatrix::ProyectionMatrix);
		//WaterMaterial->SetMat4("v", CameraMatrix::ViewMatrix);
		WaterMaterial->SetFloat("time", TimeWaves);
		WaterMaterial->SetFloat("Alpha", 0.2f);
	}
};

#endif