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
		ecsystem.second->update();
	}
}

void World::draw()
{
	for(auto& ecsystem : m_systems)
	{
		ecsystem.second->draw();
	}
}