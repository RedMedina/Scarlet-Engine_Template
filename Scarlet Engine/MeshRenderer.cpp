#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(const char* modelpath, glm::vec3* pos, glm::vec3* rot, glm::vec3* sca)
{
    ModelLoader = new StaticMeshLoader;
    ModelLoader->LoadObj(modelpath, vertices, uvs, normals);

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

    
    //vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    //uvs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    //normals
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    

    position = pos;
    rotation = rot;
    scale = sca;
}

void MeshRenderer::SetMaterial(Material* m)
{  
    mat = m;

    if (MainLightData::DIRECTIONAL_LIGHT_SHADOWMAP)
    {
        Material::Texture tex;
        tex.IdTexture = *MainLightData::DEPTHMAP;
        //tex.IdTexture = 5;
        std::cout << "SHADOW MAP ID TEXTURE " << tex.IdTexture << endl;
        tex.Name = "shadowMap";
        mat->Textures.push_back(tex);
    }
}

Material* MeshRenderer::GetMaterial()
{
    return mat;
}

void MeshRenderer::Update()
{
    //
}

void MeshRenderer::Draw()
{
    mat->Set_Config(settings);
    mat->Draw();

    //Set Model Matrix
    glm::mat4 RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation->x), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation->y), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation->z), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 TranslationMatrix = glm::translate(glm::mat4(1.0f), *position);
    glm::mat4 ScalingMatrix = glm::scale(glm::mat4(1.0f), *scale);
    glm::mat4 model = TranslationMatrix * RotationMatrix * ScalingMatrix;
    glm::mat4 mvp = CameraMatrix::ProyectionMatrix * CameraMatrix::ViewMatrix * model;

    mat->SetMat4("mvp", mvp);
    mat->SetMat4("m", model);
    mat->SetVec3("light_direction", *MainLightData::MainLightPos);
    mat->SetVec3("light_color", *MainLightData::MainLightColor);
    mat->SetVec3("light_specular", *MainLightData::MainLightSpecular);
    mat->SetVec3("light_diffuse", *MainLightData::MainLightDiffuse);
    mat->SetVec3("viewPos", *CameraMatrix::CameraPosition);

    if(GetPointLights)
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

    if(MainLightData::DIRECTIONAL_LIGHT_SHADOWMAP)
    {
        mat->SetMat4("lightSpaceMatrix", MainLightData::lightSpaceMatrix);
    }

    if(HDRColor)
    {
        mat->SetInteger("HDR", true);
        if(MainSettings::RenderN == MainSettings::NumRenders)
        {
            ImGui::SliderFloat("Exposure", &exposure, 0.0f, 4.0f);
        }
    }

    mat->SetFloat("exposure", exposure);

    glBindVertexArray(VertexArrayID);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);

    mat->End_Config(settings);
}