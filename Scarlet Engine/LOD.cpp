#include "LOD.h"

LOD::LOD(glm::vec3* pos, glm::vec3* rot, glm::vec3* sca)
{
	position = pos;
	rotation = rot;
	scale = sca;

	for (LodItem Obj : LOD_Levels) {
		dynamic_cast<Transform*>(Obj.objLod->components[0])->Position = *position;
		dynamic_cast<Transform*>(Obj.objLod->components[0])->Rotation = *rotation;
		//dynamic_cast<Transform*>(Obj.objLod->components[0])->Scale = *scale;
	}
}

void LOD::Update()
{
	//...
}

void LOD::Draw()
{
	float Actual_distance = CalcDistance();
	for (int i = 0; i < LOD_Levels.size(); i++)
	{
		if(Actual_distance < LOD_Levels[i].MAX_RENDER_distance)
		{
			dynamic_cast<Transform*>(LOD_Levels[i].objLod->components[0])->Position = *position;
			dynamic_cast<Transform*>(LOD_Levels[i].objLod->components[0])->Rotation = *rotation;
			//dynamic_cast<Transform*>(LOD_Levels[i].objLod->components[0])->Scale = *scale;

			LOD_Levels[i].objLod->Draw();
			break;
		}
	}
}

float LOD::CalcDistance()
{
	float dx = CameraMatrix::CameraPosition->x - position->x;
	float dy = CameraMatrix::CameraPosition->y - position->y;
	float dz = CameraMatrix::CameraPosition->z - position->z;

	float distance = std::sqrt(dx * dx + dy * dy + dz * dz);

	return distance;
}