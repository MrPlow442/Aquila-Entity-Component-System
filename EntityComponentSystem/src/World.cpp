#include <algorithm>
#include "../Include/World.h"

World::World() {}

Entity& World::createEntity()
{
	//TODO: Add MT support
	m_entities.push_back( EntityPtr(new Entity(m_identifierPool.checkOut())) );

	return *m_entities.back();
}

void World::destroyEntity( Entity& entity )
{
	m_identifierPool.checkIn(entity.getId());

	m_entities.erase(
		std::remove_if(m_entities.begin(), m_entities.end(), 
		[&, this](EntityPtr& m_entity) 
		{
			return m_entity.get() == &entity;
		}), m_entities.end());
}

void World::update()
{
	for(auto& ecsystem : m_systems)
	{
		if(ecsystem.second->enabled())
		{
			std::bitset< 64 >& lockbits = ecsystem.second->getLockBits();
			for( auto& entity : m_entities )
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
			for( auto& entity : m_entities )
			{
				if( (entity->getKeyBits() & lockbits) == lockbits )
				{
					ecsystem.second->draw( entity->getRelevantComponents( lockbits ) );
				}
			}
		}
	}
}