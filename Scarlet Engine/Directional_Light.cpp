#include "Directional_Light.h"

Directional_Light::Directional_Light(glm::vec3* Direction, glm::vec3* AmbientColor, glm::vec3* DiffuseColor, glm::vec3* SpecularColor, bool mainLight)
{
	this->Direction = Direction;
	this->AmbientColor = AmbientColor;
	this->DiffuseColor = DiffuseColor;
	this->SpecularColor = SpecularColor;
	this->isMainLight = mainLight;

	if (isMainLight)
	{
		MainLightData::MainLightPos = this->Direction;
		MainLightData::MainLightColor = this->AmbientColor;
		MainLightData::MainLightSpecular = this->SpecularColor;
		MainLightData::MainLightDiffuse = this->DiffuseColor;
	}
}

void Directional_Light::Update()
{
	//
}

void Directional_Light::Draw()
{
	//GuiIm Att
	if(MainSettings::RenderN == MainSettings::NumRenders)
	{
		ImGui::ColorPicker3("Dir Ambient", &AmbientColor->x);
		ImGui::ColorPicker3("Dir Specular", &SpecularColor->x);
		ImGui::ColorPicker3("Dir Diffuse", &DiffuseColor->x);
		ImGui::Checkbox("Emit shadow", &EmitShadow);
	}
	
	if(EmitShadow)
	{
		MainLightData::SHADOW_HEIGHT = 1024;
		MainLightData::SHADOW_WIDTH = 1024;
		MainLightData::DIRECTIONAL_LIGHT_SHADOWMAP = EmitShadow;
	}

	if(isMainLight)
	{
		MainLightData::MainLightPos = Direction;
		MainLightData::MainLightColor = AmbientColor;
		MainLightData::MainLightSpecular = SpecularColor;
		MainLightData::MainLightDiffuse = DiffuseColor;
	}
}