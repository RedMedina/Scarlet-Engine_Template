#include "Point_Light.h"

Point_Light::Point_Light(glm::vec3* Position, glm::vec3* AmbientColor, glm::vec3* DiffuseColor, glm::vec3* SpecularColor, float Constant, float Linear, float Cuadratic, bool mainLight)
{
	this->Position = Position;
	this->AmbientColor = AmbientColor;
	this->DiffuseColor = DiffuseColor;
	this->SpecularColor = SpecularColor;
	this->Constant = Constant;
	this->Linear = Linear;
	this->Cuadratic = Cuadratic;
	this->isMainLight = mainLight;

	if(!isMainLight)
	{
		MainLightData::Point_Lights.push_back(this);
	}
}

void Point_Light::Update()
{
	//
}

void Point_Light::Draw()
{
	//GuiIm Att
	if (MainSettings::RenderN == MainSettings::NumRenders)
	{
		ImGui::ColorPicker3(("Point Ambient " + std::to_string(UINum)).c_str(), &AmbientColor->x);
		ImGui::ColorPicker3(("Point Specular " + std::to_string(UINum)).c_str(), &SpecularColor->x);
		ImGui::ColorPicker3(("Point Diffuse " + std::to_string(UINum)).c_str(), &DiffuseColor->x);
		ImGui::SliderFloat(("Constant " + std::to_string(UINum)).c_str(), &this->Constant, 0.0f, 4.0f);
		ImGui::SliderFloat(("Linear " + std::to_string(UINum)).c_str(), &this->Linear, 0.0f, 2.0f);
		ImGui::SliderFloat(("Cuadratic " + std::to_string(UINum)).c_str(), &this->Cuadratic, 0.0f, 2.0f);
	}

	if (isMainLight)
	{
		MainLightData::MainLightPos = Position;
		MainLightData::MainLightColor = AmbientColor;
		MainLightData::MainLightSpecular = SpecularColor;
		MainLightData::MainLightDiffuse = DiffuseColor;
	}
}
