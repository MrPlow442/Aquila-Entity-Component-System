#include "Entity.h"
#include "ComponentExtractor.h"
#include "../Components/Component.h"

Entity::Entity(unsigned int id) 
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

ComponentExtractor Entity::getRelevantComponents( std::bitset<64>& lockBits )
{
	ComponentExtractor extractor;

	for(auto& mapItem : m_componentMap)
	{
		auto key = mapItem.first;
		if(lockBits.test(key))
		{
			extractor.m_relevantComponentMap.insert( std::make_pair( key, mapItem.second));
		}
	}
	return extractor;
}
