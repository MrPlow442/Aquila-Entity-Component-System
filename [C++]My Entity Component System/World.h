#ifndef WORLD_H
#define WORLD_H

#include "Systems/System.h"
#include "Entity/EntityManager.h"

#include <unordered_map>
#include <memory>

typedef std::unique_ptr< SystemBase > SystemPtr;

/**
 * World
 * Manages the whole Entity Component System 
 * while hopefully providing a simple and safe interface
 * 
 * Takes care of creating / destroying entities and systems
 */
class World
{
public:
	World();
	
	EntityManager& getEntityManager();

	void update();
	void draw();

	Entity& createEntity();
	void destroyEntity(Entity& entity );

	template<typename T> void createSystem();
	template<typename T> void removeSystem();
	template<typename T> void disableSystem();
	template<typename T> void enableSystem();
private:
	template<typename T> bool systemExists();

	std::unordered_map< unsigned int, SystemPtr > m_systems;
	EntityManager m_entityManager;
};

template<typename T> bool World::systemExists()
{
	return m_systems.find(T::systemType()) !=  m_systems.end();
}

template<typename T> void World::createSystem()
{
	static_assert(std::is_base_of< SystemBase, T >::value, "Supplied Type is not derived from System");
	if( !systemExists<T>() )
	{
		m_systems.insert( std::make_pair( T::systemType(), std::move( SystemPtr( new T() ) ) ) );
	}
}


template<typename T> void World::enableSystem()
{
	static_assert(std::is_base_of< SystemBase, T >::value, "Supplied Type is not derived from System");
	if( systemExists<T>() ) 
	{
		m_systems.at( T::systemType() )->enable();
	}
}

template<typename T> void World::disableSystem()
{
	static_assert(std::is_base_of< SystemBase, T >::value, "Supplied Type is not derived from System");
	if( systemExists<T>() ) 
	{
		m_systems.at( T::systemType() )->disable();
	}
}

template<typename T> void World::removeSystem()
{
	if( systemExists<T>() )
	{
		m_systems.erase( T::systemType() );
	}
}
#endif // WORLD_H
