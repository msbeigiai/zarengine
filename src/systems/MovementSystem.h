#pragma once
#include "../ecs/ECS.h"

class MovementSystem : public System {
public:
	MovementSystem() {
		// Interested in only transform, and velocity component
	}

	void Update() {

		for (auto entity : GetEntities()) {
			// Update entity position
		}
		

	}
};

