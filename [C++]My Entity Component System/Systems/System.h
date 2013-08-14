#ifndef SYSTEM_H
#define SYSTEM_H

#include <bitset>
#include "../Components/Component.h"
#include "../Entity/EntityManager.h"
#include "../Entity/ComponentExtractor.h"

class World;

class SystemBase
{
protected:
	World& m_owner;
	EntityManager& m_entityManager;
	std::bitset<64> m_lockBits;
	bool m_enabled;
	template<typename Component> void addComponentType();
	virtual void updateEntity(ComponentExtractor& extractor) = 0;
	virtual void drawEntity(ComponentExtractor& extractor) {}
public:
	SystemBase(World& owner);
	void update();
	void draw();

	void enable();
	void disable();
	bool enabled();

	std::bitset<64>& getLockBits();
	virtual int getSystemType() = 0;
};

template<class T> class System : public SystemBase
{
protected:
	static int m_type;
public:
	System(World& owner) : SystemBase(owner) {}
	static int systemType() { return m_type; }
	int getSystemType() { return T::m_type; }
};

static int nextSystemType = 0;
template<typename T> int System<T>::m_type(nextSystemType++);

template<typename Component> void SystemBase::addComponentType()
{
	m_lockBits.set(Component::type());
}
#endif // SYSTEM_H
