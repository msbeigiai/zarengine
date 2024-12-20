#pragma once

#include "../ecs/ECS.h"
#include "../components/ProjectileComponent.h"
#include <SDL.h>

class ProjectileLifecycleSystem : public System {
public:
	ProjectileLifecycleSystem() {
		RequireComponent<ProjectileComponent>();
	}

	void Update() {
		for (auto entity : GetSystemEntities()) {
			const auto projectile = entity.GetComponent<ProjectileComponent>();

			// TODO
			if (SDL_GetTicks() - projectile.startTime > projectile.duration) {
				entity.Kill();
			}
		}
	}
};

