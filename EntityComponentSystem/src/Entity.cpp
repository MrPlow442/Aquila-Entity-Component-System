#include "..\Aquila\Include\Entity.h"
#include "..\Aquila\Include\ComponentProvider.h"
#include "..\Aquila\Include\Component.h"

namespace aq
{
	Entity::Entity( unsigned int id ) 
	{
		m_id = id;
	}

	Entity::~Entity() {}

	unsigned int Entity::getId()
	{
		return m_id;
	}

	void Entity::addComponent( ComponentBase* component )
	{
		//TODO: Add MT support
		BaseComponentPtr temp(component);
		if(m_keyBits.at(temp->getType())) return; //If component bit is set, do nothing

		m_keyBits.set(temp->getType());
		m_componentMap.insert(std::make_pair(temp->getType(), std::move(temp)));
	}

	std::bitset<64>& Entity::getKeyBits()
	{
		return m_keyBits;
	}

	ComponentProvider Entity::getRelevantComponents( std::bitset< 64 >& lockBits )
	{
		ComponentProvider provider;

		for( auto& mapItem : m_componentMap )
		{
			auto key = mapItem.first;
			if( lockBits.test( key ) )
			{
				provider.m_relevantComponentMap.insert( std::make_pair( key, mapItem.second) );
			}
		}
		return provider;
	}
}
