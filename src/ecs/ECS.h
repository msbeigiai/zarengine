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
	int numEntity = 0;

	// Vector of components Pool
	std::vector<IPool*> componentPool;

};

template <typename TComponent>
void System::RequireComponent() {
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}


