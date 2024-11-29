#pragma once

#include <string>
#include <SDL.h>

struct SpriteComponent {
	std::string assetId;
	int width;
	int height;
	SDL_Rect srcRect;

	SpriteComponent(std::string assetId = "", int width = 0, int height = 0, int srcRectX = 0, int srcRectY = 0) {
		this->assetId = assetId;
		this->height = height;
		this->width = width;
		this->srcRect = { srcRectX, srcRectY, width, height };
	}
};
