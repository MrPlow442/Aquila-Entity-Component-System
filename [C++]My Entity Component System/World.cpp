#include "World.h"

World::World() {}

Entity& World::createEntity()
{
	return m_entityManager.createEntity();
}

void World::destroyEntity( Entity& entity )
{
	m_entityManager.destroyEntity(entity);
}

EntityManager& World::getEntityManager()
{
	return m_entityManager;
}

void World::update()
{
	for(auto& ecsystem : m_systems)
	{
		if(ecsystem.second->enabled())
		{
			std::bitset< 64 >& lockbits = ecsystem.second->getLockBits();
			for( auto& entity : m_entityManager.getEntityList() )
			{
				if( (entity->getKeyBits() & lockbits) == lockbits )
				{
					ecsystem.second->update( entity->getRelevantComponents( lockbits ) );
				}
			}
		}
	}
}

void World::draw()
{
	for(auto& ecsystem : m_systems)
	{
		if(ecsystem.second->enabled())
		{
			std::bitset< 64 >& lockbits = ecsystem.second->getLockBits();
			for( auto& entity : m_entityManager.getEntityList() )
			{
				if( (entity->getKeyBits() & lockbits) == lockbits )
				{
					ecsystem.second->draw( entity->getRelevantComponents( lockbits ) );
				}
			}
		}
	}
}