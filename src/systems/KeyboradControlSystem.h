#pragma once

#include "../ecs/ECS.h"
#include "../event_bus/EventBus.h"
#include "../events/KeyPressedEvent.h"
#include "../logger/Logger.h"
#include "../components/SpriteComponent.h"
#include "../components/RigidBodyComponent.h"
#include "../components/KeyboardControlledComponent.h"
#include <SDL.h>

class KeyboardControlSystem : public System 
{ 
public:
	KeyboardControlSystem(){
		RequireComponent<KeyboardControlledComponent>();
		RequireComponent<RigidBodyComponent>();
		RequireComponent<SpriteComponent>();
	}

	void SubscribeToEvent(std::unique_ptr<EventBus>& eventBus)
	{ 
		eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyPressed);
	}

	void OnKeyPressed(KeyPressedEvent& event)
	{
		for (auto entity : GetSystemEntities())
		{
			const auto keyboardControl = entity.GetComponent<KeyboardControlledComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();
			auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

			switch (event.symbol)
			{
			case SDLK_UP:
				rigidbody.velocity = keyboardControl.upVelocity;
				sprite.srcRect.y = sprite.height * 0;
				break;

			case SDLK_RIGHT:
				rigidbody.velocity = keyboardControl.rightVelocity;
				sprite.srcRect.y = sprite.height * 1;
				break;

			case SDLK_DOWN:
				rigidbody.velocity = keyboardControl.downVelocity;
				sprite.srcRect.y = sprite.height * 2;
				break;

			case SDLK_LEFT:
				rigidbody.velocity = keyboardControl.leftVelocity;
				sprite.srcRect.y = sprite.height * 3;
				break;

			default:
				break;
			}

		}
	}

	void Update()
	{

	}
};
