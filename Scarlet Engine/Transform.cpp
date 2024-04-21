#include "Transform.h"

Transform::Transform(float x, float y, float z, float RotX, float RotY, float RotZ, float ScaleX, float ScaleY, float ScaleZ)
{
	Position.x = x;
	Position.y = y;
	Position.z = z;

	Rotation.x = RotX;
	Rotation.y = RotY;
	Rotation.z = RotZ;

	Scale.x = ScaleX;
	Scale.y = ScaleY;
	Scale.z = ScaleZ;
}

void Transform::Update()
{
	
}

void Transform::Draw()
{

}