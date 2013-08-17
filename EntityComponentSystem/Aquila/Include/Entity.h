#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <bitset>
#include <unordered_map>
#include <type_traits>
#include <stdexcept>

namespace aq
{
	class ComponentProvider;

	struct ComponentBase;

	typedef std::shared_ptr< ComponentBase > BaseComponentPtr;

	/**
	 * Entity
	 * Class representing an entity
	 * Contains components and allows control over them
	 */
	class Entity
	{
	public:
		Entity( unsigned int id );
		~Entity();

		std::bitset<64>& getKeyBits();

		/**
		 * Adds a new component to this entity
		 */
		void addComponent( ComponentBase* component );

		/**
		 * Retrieves a special map of components which match systems lock bits
		 */
		ComponentProvider getRelevantComponents( std::bitset< 64 >& lockBits );

		/**
		 * Attempts to retrieve component of type T
		 * returns component pointer on success or nullptr on failure
		 */
		/*template< typename T > typename std::shared_ptr< T >& getComponent();*/

		/**
		 * Disables a component
		 * disabled components remain in the component map
		 * but are not visible to component extractors and systems
		 */
		template< typename T > void disableComponent();

		/**
		 * Enables a component
		 * makes a disabled component visible
		 */
		template< typename T > void enableComponent();
	
		/**
		 * Removes a component from this entity
		 */
		template< typename T > void removeComponent();

		/**
		 * Retrieves the entity id
		 */
		unsigned int getId();

	private:
		unsigned int m_id;
		std::unordered_map< unsigned int, BaseComponentPtr > m_componentMap;
		std::bitset< 64 > m_keyBits;
	};

	//template< typename T > typename std::shared_ptr< T >& Entity::getComponent()
	//{
	//	static_assert( std::is_base_of< ComponentBase, T >::value, "Supplied Type is not derived from Component" );
	//	try
	//	{
	//		return std::static_pointer_cast< T >( m_componentMap.at( T::type() ) );
	//	}
	//	catch ( const std::out_of_range& e )
	//	{
	//		std::cerr << e.what() << std::endl;
	//		std::cerr << "Component doesn't exist" << std::endl;
	//		return nullptr;
	//	}
	//}

	template< typename T > void Entity::disableComponent()
	{
		static_assert( std::is_base_of< ComponentBase, T >::value, "Supplied Type is not derived from Component" );
		m_keyBits.reset( T::type() );
	}

	template< typename T > void Entity::enableComponent()
	{
		static_assert( std::is_base_of< ComponentBase, T >::value, "Supplied Type is not derived from Component" );
		if(m_componentMap.find( T::type() ) != m_componentMap.end())
			m_keyBits.set( T::type() );
	}

	template< typename T > void Entity::removeComponent()
	{
		static_assert( std::is_base_of< ComponentBase, T >::value, "Supplied Type is not derived from Component" );
		m_componentMap.erase( T::type() );
		m_keyBits.reset( T::type() );
	}
}
#endif // ENTITY_H