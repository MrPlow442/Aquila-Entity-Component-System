#include "EntityManager.h"
#include "Entity.h"
#include <algorithm>

EntityManager::EntityManager() {}

EntityManager::~EntityManager() {}

Entity& EntityManager::createEntity()
{
	//TODO: Add MT support
	m_entities.push_back( EntityPtr(new Entity(m_identifierPool.checkOut())) );
	
	return *m_entities.back();
}

void EntityManager::destroyEntity( Entity& entity )
{
	m_identifierPool.checkIn(entity.getId());

	m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), 
		[&, this](EntityPtr& m_entity) {
			return m_entity.get() == &entity;
	}), m_entities.end());
}

std::vector< EntityPtr >& EntityManager::getEntityList()
{
	return m_entities;
}
