#pragma once

#include "../ecs/ECS.h"
#include "../components/SpriteComponent.h"
#include "../components/TransformComponent.h"
#include <SDL.h>

class RenderSystem : public System {
public:
	RenderSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();

	}

	void Update(SDL_Renderer* renderer) {
		for (auto entity : GetSystemEntities()) {
			const auto& transform = entity.GetComponent<TransformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();

			SDL_Rect object = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				sprite.width,
				sprite.height
			};
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &object);
		}
	}
};
