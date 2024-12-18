#pragma once

#include "../ecs/ECS.h"
#include "../components/CameraFollowComponent.h"
#include "../components/TransformComponent.h"
#include <SDL.h>

class CameraMovementSystem : public System
{
public:
	CameraMovementSystem()
	{
		RequireComponent<CameraFollowComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(SDL_Rect& camera)
	{
		for (auto entity : GetSystemEntities())
		{
			auto transform = entity.GetComponent<TransformComponent>();

			// TODO
			if (transform.position.x + (camera.w / 2) < Game::mapWidth)
			{
				camera.x = transform.position.x - (Game::windowWidth / 2);
			}
			if (transform.position.y + (camera.h / 2) < Game::mapHeight)
			{
				camera.y = transform.position.y - (Game::windowHeight / 2);
			}

			// Keep camera view rectangle inside the screen limits
			camera.x = camera.x < 0 ? 0 : camera.x;
			camera.y = camera.y < 0 ? 0 : camera.y;
			camera.x = camera.x > camera.w ? camera.w : camera.x;
			camera.y = camera.y > camera.h ? camera.h : camera.y;

			Logger::Log("Camera changed its position to: " + std::to_string(camera.y));
		}
	}

};
