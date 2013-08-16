#ifndef COMPONENTEXTRACTOR_H
#define COMPONENTEXTRACTOR_H

#include "Component.h"
#include "Entity.h"

#include <iostream>
#include <unordered_map>
#include <stdexcept>

namespace aq
{
	/**
	 * ComponentExtractor
	 * class used to contain and provide access to requested components
	 * Note: Probably should have named this ComponentProvider instead
	 */
	typedef std::shared_ptr< ComponentBase > BaseComponentPtr;
	class ComponentExtractor
	{
	public:
		ComponentExtractor();
		~ComponentExtractor(); 

		friend void swap( ComponentExtractor& first, ComponentExtractor& second );
		ComponentExtractor( ComponentExtractor&& other );
		/*ComponentExtractor& operator=( ComponentExtractor&& other );*/
		ComponentExtractor& operator=( ComponentExtractor other );

		/**
		 * Attempts to retrieve component of type T
		 * returns component pointer on success or nullptr on failure
		 */
		template< typename T > typename std::shared_ptr< T > getComponent();

		friend class Entity;
	private:
		std::unordered_map< unsigned int , BaseComponentPtr > m_relevantComponentMap;
	};

	template< typename T > typename std::shared_ptr< T > ComponentExtractor::getComponent()
	{
		static_assert( std::is_base_of< ComponentBase, T >::value, "Supplied Type is not derived from Component");
		try
		{
			return std::static_pointer_cast< T >( m_relevantComponentMap.at( T::type() ) );
		}
		catch ( const std::out_of_range& e )
		{
			std::cerr << e.what() << std::endl;
			std::cerr << "Component doesn't exist" << std::endl;
			return nullptr;
		}
	}
}
#endif // COMPONENTEXTRACTOR_H
