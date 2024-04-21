#ifndef __WaterEffect
#define __WaterEffect

#include "Component.h"
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
		TimeWaves += 0.05f;
		WaterMaterial->SetFloat("time", TimeWaves);
	}
};

#endif