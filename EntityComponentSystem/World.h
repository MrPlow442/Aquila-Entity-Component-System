#ifndef WORLD_H
#define WORLD_H

#include "Systems/System.h"

#include <unordered_map>
#include <memory>
#include <functional>

typedef std::unique_ptr< SystemBase > SystemPtr;
typedef std::unique_ptr< Entity > EntityPtr;

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

	void update();
	void draw();

	Entity& createEntity();
	void destroyEntity(Entity& entity );

	template<typename T> void createSystem();
	template<typename T> void removeSystem();
	template<typename T> void disableSystem();
	template<typename T> void enableSystem();

private: 
	// Nested class for entity id distribution
	class IdentifierPool
	{
	private:
		std::vector<unsigned int> m_idPool;
		unsigned int m_nextId;
	public:
		IdentifierPool() : m_nextId(0) {}
		~IdentifierPool() {}

		void checkIn( unsigned int id )
		{
			m_idPool.push_back(id);
		}

		int checkOut()
		{
			if(!m_idPool.empty())
			{
				unsigned int last = m_idPool.back();
				m_idPool.pop_back();
				return last;
			}
			return m_nextId++;
		}
	};
	// Private methods
	template<typename T> bool systemExists();
	// Data
	std::unordered_map< unsigned int, SystemPtr > m_systems;
	std::vector< EntityPtr > m_entities;
	IdentifierPool m_identifierPool;
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
