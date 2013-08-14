#include "ComponentExtractor.h"


ComponentExtractor::ComponentExtractor() {}

ComponentExtractor::~ComponentExtractor() {}

ComponentExtractor::ComponentExtractor( ComponentExtractor&& other )
{
	m_relevantComponentMap = other.m_relevantComponentMap;
	other.m_relevantComponentMap.clear();
}

ComponentExtractor& ComponentExtractor::operator=( ComponentExtractor&& other )
{
	if(this != &other)
	{
		m_relevantComponentMap.clear();
		m_relevantComponentMap = other.m_relevantComponentMap;
		other.m_relevantComponentMap.clear();
	}
	return *this;
}
