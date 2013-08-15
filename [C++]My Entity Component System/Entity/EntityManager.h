#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "../Components/Component.h"
#include "Entity.h"

#include <vector>
#include <memory>
#include <iostream>

typedef std::unique_ptr< Entity > EntityPtr;
/**
 * EntityManager
 * Takes care of creation and destruction of entities
 */
class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	/**
	 * Creates a new entity and adds it to the entity list
	 * returns a reference to the newly created entity
	 */
	Entity& createEntity();

	/**
	 * Destroy the given entity
	 */
	void destroyEntity( Entity& entity );

	/**
	 * Retrieves a list of currently active entities
	 */
	std::vector< EntityPtr >& getEntityList();
private:
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
private:
	std::vector< EntityPtr > m_entities;
	IdentifierPool m_identifierPool;
};
#endif // ENTITYMANAGER_H
