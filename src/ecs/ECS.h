#pragma once

#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENT = 32;

// Signature
typedef std::bitset<MAX_COMPONENT> Signature;

struct IComponent {
protected:
	static int nextId;
};

template <typename T>
class Component : public IComponent {
	static const int GetId() {
		static auto id = nextId++;
		return id;
	}
};

class Entity {
private:
	int id;

public:
	Entity(int id) :id(id) {};
	Entity(const Entity&) = default;
	int GetId() const;

	Entity& operator=(const Entity& other) = default;
	bool operator == (const Entity& other) const { return id == other.GetId(); }
	bool operator !=(const Entity& other) const { return id != other.GetId(); }
	bool operator >(const Entity& other) const { return id > other.GetId(); }
	bool operator <(const Entity& other) const { return id < other.GetId(); }

};

class System {
private:
	Signature componentSignature;
	std::vector<Entity> entities;

public:
	System() = default;
	virtual ~System() = default;

	void AddEntityToSystem(Entity entity);
	void RemoveEntityFromSystem(Entity entity);
	std::vector<Entity> GetSystemEntities() const;
	const Signature& GetComponentSignature() const;

	template <typename TComponent> void RequireComponent();
};

class Registry {};

template <typename TComponent>
void System::RequireComponent() {
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}

