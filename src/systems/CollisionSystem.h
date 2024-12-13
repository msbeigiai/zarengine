#pragma once

#include "../ecs/ECS.h"
#include "../event_bus/EventBus.h"
#include "../events/CollisionEvent.h"
#include "../components/BoxColliderComponent.h"
#include "../components/TransformComponent.h"

class CollisionSystem : public System
{
public:
	CollisionSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<BoxColliderComponent>();
	}

	void Update(std::unique_ptr<EventBus>& eventBus) {
		auto entities = GetSystemEntities();

		for (auto i = entities.begin(); i != entities.end(); i++)
		{
			Entity a = *i;
			auto aTransform = a.GetComponent<TransformComponent>();
			auto aCollider = a.GetComponent<BoxColliderComponent>();

			for (auto j = i; j != entities.end(); j++)
			{
				Entity b = *j;

				if (a == b)
				{
					continue;
				}

				auto bTransform = b.GetComponent<TransformComponent>();
				auto bCollider = b.GetComponent<BoxColliderComponent>();

				// Check for the collision between a and b
				// AABB collision check
				bool collisionHappened = CheckAABBCollision(
					aTransform.position.x + aCollider.offset.x,
					aTransform.position.y + aCollider.offset.y,
					aCollider.width,
					aCollider.height,
					bTransform.position.x + bCollider.offset.x,
					bTransform.position.y + bCollider.offset.y,
					bCollider.width,
					bCollider.height
				);

				if (collisionHappened)
				{
					Logger::Log("Entity " + std::to_string(a.GetId()) + " is colliding with entity " + std::to_string(b.GetId()));
					eventBus->EmitEvent<CollisionEvent>(a, b);
				}

			}
		}
	}

	bool CheckAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH)
	{
		return (aX < bX + bW && aX + aW > bX && aY < bY + bH && aY + aH > bY);
	}
};
