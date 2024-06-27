#include "Terrain.h"

Terrain::Terrain(const char* heightmap)
{
	//stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(heightmap, &width, &height, &nrChannels, 0);

    if (data)
    {
        std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    float yScale = 64.0f / 256.0f, yShift = 16.0f;
    int rez = 1;
    unsigned bytePerPixel = nrChannels;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned char* pixelOffset = data + (j + width * i) * bytePerPixel;
            unsigned char y = pixelOffset[0];

            // vertex
            vertices.push_back(-height / 2.0f + height * i / (float)height);   // vx
            vertices.push_back((int)y * yScale - yShift);   // vy
            vertices.push_back(-width / 2.0f + width * j / (float)width);   // vz
        }
    }
    std::cout << "Loaded " << vertices.size() / 3 << " vertices" << std::endl;
    stbi_image_free(data);

    for (unsigned i = 0; i < height - 1; i += rez)
    {
        for (unsigned j = 0; j < width; j += rez)
        {
            for (unsigned k = 0; k < 2; k++)
            {
                indexes.push_back(j + width * (i + k * rez));
            }
        }
    }
    std::cout << "Loaded " << indexes.size() << " indices" << std::endl;

    // Calcula y almacena las coordenadas de textura (UVs) para cada vértice
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Calcula las coordenadas de textura (UVs) normalizadas
            float u = static_cast<float>(j) / static_cast<float>(width - 1);
            float v = static_cast<float>(i) / static_cast<float>(height - 1);

            // Almacena las coordenadas de textura (UVs)
            uvs.push_back(u);
            uvs.push_back(v);
        }
    }

    const int numStrips = (height - 1) / rez;
    NStrips = numStrips;
    const int numTrisPerStrip = (width / rez) * 2 - 2;
    NTrisPerStrip = numTrisPerStrip;

    CalculateNormals();

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, uvs.size() * sizeof(float), &uvs[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

    glGenBuffers(1, &indexbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned), &indexes[0], GL_STATIC_DRAW);

    //vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //uvs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    //normals
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
}

void Terrain::CalculateNormals()
{
    normals.clear();
    normals.resize(vertices.size(), glm::vec3(0.0f));

    for (unsigned strip = 0; strip < NStrips; strip++) {
        for (unsigned i = 0; i < NTrisPerStrip; i++) {
            unsigned v0Idx = indexes[strip * (NTrisPerStrip + 2) + i];
            unsigned v1Idx = indexes[strip * (NTrisPerStrip + 2) + i + 1];
            unsigned v2Idx = indexes[strip * (NTrisPerStrip + 2) + i + 2];

            glm::vec3 v0(vertices[v0Idx * 3], vertices[v0Idx * 3 + 1], vertices[v0Idx * 3 + 2]);
            glm::vec3 v1(vertices[v1Idx * 3], vertices[v1Idx * 3 + 1], vertices[v1Idx * 3 + 2]);
            glm::vec3 v2(vertices[v2Idx * 3], vertices[v2Idx * 3 + 1], vertices[v2Idx * 3 + 2]);

            glm::vec3 edge1 = v1 - v0;
            glm::vec3 edge2 = v2 - v0;
            glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

            // Suma la normal de la cara a los vértices asociados
            normals[v0Idx] += normal;
            normals[v1Idx] += normal;
            normals[v2Idx] += normal;
        }
    }

    // Normaliza las normales por vértice
    for (size_t i = 0; i < normals.size(); i++) {
        normals[i] = glm::normalize(normals[i]);
    }
}

void Terrain::SetMaterial(Material* m)
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

void Terrain::Update()
{
    //...
}

void Terrain::Draw()
{
    if(MainSettings::RenderN > 1){

    

    mat->Set_Config(settings);
    mat->Draw();
    glm::mat4 model = glm::mat4(1.0f);
    mat->SetMat4("model", model);
    mat->SetMat4("view", CameraMatrix::ViewMatrix);
    mat->SetMat4("projection", CameraMatrix::ProyectionMatrix);
    mat->SetMat4("lightSpaceMatrix", MainLightData::lightSpaceMatrix);
    mat->SetVec3("viewPos", *CameraMatrix::CameraPosition);
    mat->SetVec3("light_direction", *MainLightData::MainLightPos);

    mat->SetVec3("light_color", *MainLightData::MainLightColor);
    mat->SetVec3("light_specular", *MainLightData::MainLightSpecular);
    mat->SetVec3("light_diffuse", *MainLightData::MainLightDiffuse);

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


    glBindVertexArray(VertexArrayID);
    for (unsigned strip = 0; strip < NStrips; strip++)
    {
        glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
            NTrisPerStrip + 2,   // number of indices to render
            GL_UNSIGNED_INT,     // index data type
            (void*)(sizeof(unsigned) * (NTrisPerStrip + 2) * strip)); // offset to starting index
    }

    mat->End_Config(settings);

    }
}

Terrain::~Terrain()
{
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
}