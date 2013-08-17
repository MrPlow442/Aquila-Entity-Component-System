#include "..\Aquila\Include\ComponentProvider.h"
#include <algorithm>

namespace aq
{
	ComponentProvider::ComponentProvider() {}

	ComponentProvider::~ComponentProvider() {}

	void swap( ComponentProvider& first, ComponentProvider& second )
	{
		using std::swap;
		swap(first.m_relevantComponentMap, second.m_relevantComponentMap);
	}

	ComponentProvider::ComponentProvider( ComponentProvider&& other )
	{
		swap(*this, other);
	}

	ComponentProvider& ComponentProvider::operator=( ComponentProvider other )
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
}


