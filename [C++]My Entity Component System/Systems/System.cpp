#include "System.h"
#include "../World.h"


SystemBase::SystemBase( World& owner ) :
	m_owner(owner),
	m_entityManager(owner.getEntityManager()),
	m_enabled(true) {}

void SystemBase::update()
{
	auto& entityList = m_entityManager.getEntityList();
	for(auto& ent : entityList)
	{
		if( (ent->getKeyBits() & getLockBits()) == getLockBits() )
			updateEntity( ent->getRelevantComponents( m_lockBits ) );
	}
}


void SystemBase::draw()
{
	auto& entityList = m_entityManager.getEntityList();
	for(auto& ent : entityList)
	{
		if( (ent->getKeyBits() & getLockBits()) == getLockBits() )
			drawEntity( ent->getRelevantComponents( m_lockBits ) );
	}
}


std::bitset<64>& SystemBase::getLockBits()
{
	return m_lockBits;
}

void SystemBase::enable()
{
	m_enabled = true;
}

void SystemBase::disable()
{
	m_enabled = false;
}

bool SystemBase::enabled()
{
	return m_enabled;
}
