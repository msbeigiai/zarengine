#pragma once

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>

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

class IPool {
public:
	virtual ~IPool() {}
};

template <typename T>
class Pool : public IPool {
private:
	std::vector<T> data;

public:
	Pool(int size = 100) { data.resize(size); }
	virtual ~Pool() = default;

	bool isEmpty() const { return data.empty(); }
	int GetSize() const { return data.size(); }
	void Resize(int n) { data.resize(n); }
	void Clear() { data.clear(); }
	void Add(T object) { data.push_back<T>(object); }
	void Set(int index, T object) { data[index] = object; }
	T& Get(int index) const { return static_cast<T&>(data[index]); }
	T& operator[](unsigned index) { return data[index]; }
};

// Creation and destruction of everything...
class Registry {
private:
	int numEntities = 0;

	// Vector of components Pool
	std::vector<IPool*> componentPool;
	std::vector<Signature> entityComponentSignatures;

	// Map of active systems
	std::unordered_map<std::type_index, System*> systems;

	// Set of entities to be added or remove in the next registry update
	std::set<Entity> entitiesToBeAdded;
	std::set<Entity> entitiesToBeKilled;

public:
	Registry() = default;
	void Update();

	// Entity management
	Entity CreateEntity();

	// Component management
	template <typename TComponent, typename ...TArgs > void AddComponent(Entity entity, TArgs&& ...args);
	template <typename TComponent> void RemoveComponent(Entity entity);
	template <typename TComponent> bool HasComponent(Entity entity);

	// System management
	template<typename TSystem, typename ...TArgs> void AddSystem(TArgs&& ...args);
	template<typename TSystem> void RemoveSystem();
	template<typename TSystem> bool HasSystem() const;
	template<typename TSystem> TSystem& GetSystem()  const;

	/// <summary>
	/// Checks the component signature of an entity and add the entity to the system that are 
	/// interested in it.
	/// </summary>
	/// <param name="entity"></param>
	void AddEntityToSystems(Entity entity);
};

template <typename TComponent>
void System::RequireComponent() {
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}

template <typename TComponent, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs&& ...args) {
	const auto componentId = Component::GetId();
	const auto entityId = entity.GetId();

	if (componentId >= componentPool.size()) {
		componentPool.resize(componentPool + 1, nullptr);
	}

	if (!componentPool[componentId]) {
		Pool<TComponent>* newComponentPool = new Pool<TComponent>();
		componentPool[componentId] = newComponentPool;
	}

	Pool<TComponent>* componentPool = componentPool[componentId];

	if (entityId >= componentPool->GetSize())) {
		componentPool->Resize(numEntities);
	}

	TComponent newComponent(std::forward<TArgs>(args)...);

	componentPool->Set(entityId, newComponent);

	entityComponentSignatures[entityId].set(componentId);

}

template<typename TComponent>
void Registry::RemoveComponent(Entity entity) {
	const auto componentId = Component::GetId();
	const auto entityId = entity.GetId();

	entityComponentSignatures[entityId].set(componentId, false);
}

template<typename TComponent>
bool Registry::HasComponent(Entity entity) {
	const auto componentId = Component::GetId();
	const auto entityId = entity.GetId();

	entityComponentSignatures[entityId].test(componentId);
}

// System implementations
template<typename TSystem, typename ...TArgs>
void Registry::AddSystem(TArgs && ...args) {
	TSystem* newSystem(new TSystem(std::forward<TArgs>(args)...));
	systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template<typename TSystem>
void Registry::RemoveSystem() {
	auto system = systems.find(std::type_index(typeid(TSystem)));
	systems.erase(system);
}

template<typename TSystem>
bool Registry::HasSystem() const {
	return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

template<typename TSystem>
TSystem& Registry::GetSystem() const {
	auto system = systems.find(std::type_index(typeid(TSystem)));
	return *(std::static_pointer_cast<TSystem>(system->second));
}


