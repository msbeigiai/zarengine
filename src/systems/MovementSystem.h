#pragma once

#include "../ecs/ECS.h"
#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"

class MovementSystem : public System {
public:
	MovementSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<RigidBodyComponent>();

	}

	void Update() {
		for (auto entity : GetSystemEntities()) {
			auto& transform = entity.GetComponent<TransformComponent>();
			const auto rigidbody = entity.GetComponent<RigidBodyComponent>();

			transform.position.x += rigidbody.velocity.x;
			transform.position.y += rigidbody.velocity.y;
		 }
	}
};

