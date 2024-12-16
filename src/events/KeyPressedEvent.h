#pragma once

#include "../ecs/ECS.h"
#include "../event_bus/Event.h"
#include <SDL.h>


class KeyPressedEvent : public Event
{
public:
	SDL_Keycode symbol;
	KeyPressedEvent(SDL_Keycode symbol) : symbol{ symbol } {}

};
