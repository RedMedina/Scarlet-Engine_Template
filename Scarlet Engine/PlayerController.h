#ifndef __Playercontroller
#define __Playercontroller

#include "Component.h"
#include "Transform.h"
#include "CameraMatrix.h"
#include <glm/glm.hpp>
#include "Material.h"
#include "Time.h"
#include "Input.h"

class Playercontroller : public Component
{
public:
	Transform* PlayerTransform;
	Transform* CameraPosition;
	Camera* MainCam;
	glm::vec3 cameraOffset = glm::vec3(0, 4.0f, 2.0f);
	float cameraRotationSpeed = 1.5f;
	Animator* playerAnimator;
	
	bool IsWalk = false;
	int currentAnim = 0;

	//Start
	Playercontroller(Transform* playerTransform, const glm::vec3& offset, float rotationSpeed, Transform* camerapos)
		: PlayerTransform(playerTransform), cameraOffset(offset), cameraRotationSpeed(rotationSpeed),
		CameraPosition(camerapos)
	{
	}

	//Update
	void Update() override
	{
		glm::vec3 playerPosition = PlayerTransform->Position;
		glm::vec3 cameraPosition = playerPosition + cameraOffset;
		//CameraPosition->Position = cameraPosition;
		
		if(Input::GetKeyDown(InputKey::Up))
		{
			playerPosition.z += 12.5f * Time::deltatime;
			IsWalk = true;
		}
		if (Input::GetKeyDown(InputKey::Down))
		{
			playerPosition.z -= 12.5f * Time::deltatime;
			IsWalk = true;
		}

		if (Input::GetKeyDown(InputKey::Left))
		{
			playerPosition.x += 12.5f * Time::deltatime;
			IsWalk = true;
		}
		if (Input::GetKeyDown(InputKey::Right))
		{
			playerPosition.x -= 12.5f * Time::deltatime;
			IsWalk = true;
		}

		if(Input::GetKey(InputKey::Q))
		{
			if (currentAnim != 2)
			{
				playerAnimator->PlayAnimation(2);
				currentAnim = 2;
			}
		}

		if(Input::GetKeyUp(InputKey::Up) && Input::GetKeyUp(InputKey::Down)
			&& Input::GetKeyUp(InputKey::Right) && Input::GetKeyUp(InputKey::Left))
		{
			IsWalk = false;
		}

		if(IsWalk)
		{
			if(currentAnim != 1)
			{
				playerAnimator->PlayAnimation(1);
				currentAnim = 1;
			}
		}
		else
		{
			if (currentAnim != 0)
			{
				playerAnimator->PlayAnimation(0);
				currentAnim = 0;
			}
		}

		PlayerTransform->Position = playerPosition;
	}

	void Draw() override
	{
		
	}
};

#endif