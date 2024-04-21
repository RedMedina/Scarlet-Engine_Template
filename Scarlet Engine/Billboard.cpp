#include "Billboard.h"

Billboard::Billboard(glm::vec3* pos, glm::vec3* sca)
{
	position = pos;
	scale = sca;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = {
			 -0.5f, -0.5f, 0.0f,
			  0.5f, -0.5f, 0.0f,
			 -0.5f,  0.5f, 0.0f,
			  0.5f,  0.5f, 0.0f,
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);

	//vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void Billboard::SetMaterial(Material* m)
{
	mat = m;
}

void Billboard::Update()
{
	//...
}

void Billboard::Draw()
{
	mat->Set_Config(settings);
	mat->Draw();

	mat->SetVec3("BillboardPos", *position);
	mat->SetVec2("BillboardSize", glm::vec2(scale->x, scale->y));

	glm::mat4 vp = CameraMatrix::ProyectionMatrix * CameraMatrix::ViewMatrix;
	mat->SetMat4("VP", vp);
	mat->SetVec3("CameraRight_worldspace", glm::vec3(CameraMatrix::ViewMatrix[0][0], CameraMatrix::ViewMatrix[1][0], CameraMatrix::ViewMatrix[2][0]));
	mat->SetVec3("CameraUp_worldspace", glm::vec3(CameraMatrix::ViewMatrix[0][1], CameraMatrix::ViewMatrix[1][1], CameraMatrix::ViewMatrix[2][1]));
	mat->SetVec3("LightAmbientColor", *MainLightData::MainLightColor);

	glBindVertexArray(VertexArrayID);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	mat->End_Config(settings);
}

Billboard::~Billboard()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
}