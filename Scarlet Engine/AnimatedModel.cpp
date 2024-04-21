#include "AnimatedModel.h"

AnimatedModel::AnimatedModel(const char* modelpath, Material* m, glm::vec3* pos, glm::vec3* rot, glm::vec3* sca)
{
    mat = m;
    if (MainLightData::DIRECTIONAL_LIGHT_SHADOWMAP)
    {
        Material::Texture tex;
        tex.IdTexture = *MainLightData::DEPTHMAP;
        tex.Name = "shadowMap";
        mat->Textures.push_back(tex);
    }
    stbi_set_flip_vertically_on_load(true);
	model = new Model(modelpath, mat);
	position = pos;
	rotation = rot;
	scale = sca;
    stbi_set_flip_vertically_on_load(false);
}

void AnimatedModel::SetupAnimator()
{
    animator = new Animator(animations);
}

void AnimatedModel::SetMaterial(Material* m)
{
    mat = m;

    if (MainLightData::DIRECTIONAL_LIGHT_SHADOWMAP)
    {
        Material::Texture tex;
        tex.IdTexture = *MainLightData::DEPTHMAP;
        tex.Name = "shadowMap";
        mat->Textures.push_back(tex);
    }
}

void AnimatedModel::Update()
{
	//...
    animator->Update();
    animator->Draw();
}

void AnimatedModel::Draw()
{
    mat->Set_Config(settings);
	mat->Draw();

    glm::mat4 RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation->x), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation->y), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation->z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 TranslationMatrix = glm::translate(glm::mat4(1.0f), *position);
    glm::mat4 ScalingMatrix = glm::scale(glm::mat4(1.0f), *scale);
    glm::mat4 mod = TranslationMatrix * RotationMatrix * ScalingMatrix;
    glm::mat4 mvp = CameraMatrix::ProyectionMatrix * CameraMatrix::ViewMatrix * mod;

    mat->SetMat4("mvp", mvp);
    mat->SetMat4("m", mod);
    mat->SetMat4("v", CameraMatrix::ViewMatrix);
    mat->SetMat4("p", CameraMatrix::ProyectionMatrix);
    mat->SetVec3("light_direction", *MainLightData::MainLightPos);
    mat->SetVec3("light_color", *MainLightData::MainLightColor);
    mat->SetVec3("light_specular", *MainLightData::MainLightSpecular);
    mat->SetVec3("light_diffuse", *MainLightData::MainLightDiffuse);
    mat->SetVec3("viewPos", *CameraMatrix::CameraPosition);

    if (GetPointLights)
    {
        mat->SetInteger("NR_POINTS_LIGHTS", MainLightData::Point_Lights.size());
        for (int i = 0; i < MainLightData::Point_Lights.size(); i++)
        {
            mat->SetVec3((string("pointLights[") + to_string(i) + "].position").c_str(), *MainLightData::Point_Lights[i]->Position);
            mat->SetVec3((string("pointLights[") + to_string(i) + "].ambient").c_str(), *MainLightData::Point_Lights[i]->AmbientColor);
            mat->SetVec3((string("pointLights[") + to_string(i) + "].diffuse").c_str(), *MainLightData::Point_Lights[i]->DiffuseColor);
            mat->SetVec3((string("pointLights[") + to_string(i) + "].specular").c_str(), *MainLightData::Point_Lights[i]->SpecularColor);
            mat->SetFloat((string("pointLights[") + to_string(i) + "].constant").c_str(), MainLightData::Point_Lights[i]->Constant);
            mat->SetFloat((string("pointLights[") + to_string(i) + "].linear").c_str(), MainLightData::Point_Lights[i]->Linear);
            mat->SetFloat((string("pointLights[") + to_string(i) + "].quadratic").c_str(), MainLightData::Point_Lights[i]->Cuadratic);
        }
    }
    else
    {
        mat->SetInteger("NR_POINTS_LIGHTS", 0);
    }

    if (MainLightData::DIRECTIONAL_LIGHT_SHADOWMAP)
    {
        mat->SetMat4("lightSpaceMatrix", MainLightData::lightSpaceMatrix);
    }

    if (HDRColor)
    {
        mat->SetInteger("HDR", true);
        if (MainSettings::RenderN == MainSettings::NumRenders)
        {
            ImGui::SliderFloat("Exposure", &exposure, 0.0f, 4.0f);
        }
    }
    mat->SetFloat("exposure", exposure);

    auto transforms = animator->GetFinalBoneMatrices();
    for (int i = 0; i < transforms.size(); ++i)
    {
        mat->SetMat4((string("finalBonesMatrices[") + to_string(i) + "]").c_str(), transforms[i]);
    }


	model->Draw();

    mat->End_Config(settings);
}
