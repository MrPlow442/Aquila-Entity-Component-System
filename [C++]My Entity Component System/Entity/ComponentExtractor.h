#ifndef COMPONENTEXTRACTOR_H
#define COMPONENTEXTRACTOR_H

#include "../Components/Component.h"
#include "Entity.h"
#include <iostream>
#include <unordered_map>
#include <stdexcept>

typedef std::shared_ptr< ComponentBase > BaseComponentPtr;

class ComponentExtractor
{
private:
	std::unordered_map< unsigned int , BaseComponentPtr > m_relevantComponentMap;
public:
	ComponentExtractor();
	~ComponentExtractor(); 
	ComponentExtractor(ComponentExtractor&& other);
	ComponentExtractor& operator=(ComponentExtractor&& other);
	template<typename T> typename std::shared_ptr<T> getComponent();
	friend class Entity;
};

template<typename T> typename std::shared_ptr<T> ComponentExtractor::getComponent()
{
	static_assert(std::is_base_of< ComponentBase, T >::value, "Supplied Type is not derived from Component");
	try
	{
		return std::static_pointer_cast<T>( m_relevantComponentMap.at( T::type() ) );
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "Component doesn't exist" << std::endl;
		return nullptr;
	}
}
#endif // COMPONENTEXTRACTOR_H
