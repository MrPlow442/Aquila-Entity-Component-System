#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>
#include <iostream>

#include "../Components/Component.h"
#include "Entity.h"

typedef std::unique_ptr< Entity > EntityPtr;

class EntityManager
{
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
public:
	EntityManager();
	~EntityManager();

	Entity& createEntity();
	void destroyEntity( Entity& entity );
	std::vector< EntityPtr >& getEntityList();
};
#endif // ENTITYMANAGER_H
