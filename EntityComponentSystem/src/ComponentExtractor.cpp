#include "../Include/ComponentExtractor.h"
#include <algorithm>


ComponentExtractor::ComponentExtractor() {}

ComponentExtractor::~ComponentExtractor() {}

void swap( ComponentExtractor& first, ComponentExtractor& second )
{
	using std::swap;
	swap(first.m_relevantComponentMap, second.m_relevantComponentMap);
}

ComponentExtractor::ComponentExtractor( ComponentExtractor&& other )
{
	swap(*this, other);
}

ComponentExtractor& ComponentExtractor::operator=( ComponentExtractor other )
{
	swap(*this, other);

	return *this;
}

//ComponentExtractor& ComponentExtractor::operator=( ComponentExtractor&& other )
//{
//	if(this != &other)
//	{
//		m_relevantComponentMap.clear();
//		m_relevantComponentMap = other.m_relevantComponentMap;
//		other.m_relevantComponentMap.clear();
//	}
//	return *this;
//}


