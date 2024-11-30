#pragma once

#include "../ecs/ECS.h"
#include "../components/SpriteComponent.h"
#include "../components/TransformComponent.h"
#include "../assetstore/AssetStore.h"
#include <SDL.h>

class RenderSystem : public System {
public:
	RenderSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();

	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore) {

		for (auto entity : GetSystemEntities()) {
			const auto& transform = entity.GetComponent<TransformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();

			// Set the source rectangle and destination
			SDL_Rect srcRect = sprite.srcRect;
			SDL_Rect dstRect = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				static_cast<int>(sprite.width * transform.scale.x),
				static_cast<int>(sprite.height * transform.scale.y)
			};

			SDL_RenderCopyEx(
				renderer,
				assetStore->GetTexture(sprite.assetId),
				&srcRect,
				&dstRect,
				transform.rotation,
				NULL,
				SDL_FLIP_NONE
			);

		}
	}
};

