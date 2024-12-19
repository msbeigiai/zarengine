#pragma once

#include "../ecs/ECS.h"
#include "../components/BoxColliderComponent.h"
#include "../event_bus/EventBus.h"
#include "../events/CollisionEvent.h"

class DamageSystem : public System
{
public:
	DamageSystem()
	{
		RequireComponent<BoxColliderComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
	{
		eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::onCollision);
	}

	void onCollision(CollisionEvent& event)
	{
		Logger::Log("The damage system received an event collision between entities "
			+ std::to_string(event.a.GetId()) + ", and " + std::to_string(event.b.GetId()));

		//event.a.Kill();
		//event.b.Kill();
	}

	void Update()
	{
		Logger::Log("TEST");
	}


};
