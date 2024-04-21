#include "BoxCollider.h"

BoxCollider::BoxCollider(glm::vec3* Position, glm::vec3* Rotation, glm::vec3* Size)
{
	pos = Position;
	scale = Size; // entre 2 = (Size / 2) ?
	rotation = Rotation;

	mat = new Material("collider.vs", "collider.ps");

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	float BoxVertex[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(BoxVertex), &BoxVertex, GL_STATIC_DRAW);

	//Vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void BoxCollider::Update()
{
	//
}

void BoxCollider::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	mat->Draw();

	if(MainSettings::RenderN == MainSettings::NumRenders)
	{
		ImGui::InputFloat3("Offset Pos", &offsetPos->x);
		ImGui::InputFloat3("Offset Scale", &offsetScale->x);
		ImGui::ColorPicker4("Color Box", &boxColor->x);
		ImGui::Checkbox("Show", show);
	}

	//Set Model Matrix
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation->x), glm::vec3(1.0f, 0.0f, 0.0f))
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation->y), glm::vec3(0.0f, 1.0f, 0.0f))
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation->z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(1.0f), *pos + *offsetPos);
	glm::mat4 ScalingMatrix = glm::scale(glm::mat4(1.0f), *scale + *offsetScale);
	glm::mat4 model = TranslationMatrix * RotationMatrix * ScalingMatrix;
	glm::mat4 mvp = CameraMatrix::ProyectionMatrix * CameraMatrix::ViewMatrix * model;

	mat->SetMat4("mvp", mvp);
	mat->SetVec4("color", *boxColor);

	if(*show)
	{
		glBindVertexArray(VertexArrayID);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool BoxCollider::intersectBox(BoxCollider* box1, BoxCollider* box2)
{
	glm::vec3 box1Min = *box1->pos - *box1->scale;
	glm::vec3 box1Max = *box1->pos + *box1->scale;
	glm::vec3 box2Min = *box2->pos - *box2->scale;
	glm::vec3 box2Max = *box2->pos + *box2->scale;

	return (box1Min.x <= box2Max.x && box1Max.x >= box2Min.x) &&
		(box1Min.y <= box2Max.y && box1Max.y >= box2Min.y) &&
		(box1Min.z <= box2Max.z && box1Max.z >= box2Min.z);
}