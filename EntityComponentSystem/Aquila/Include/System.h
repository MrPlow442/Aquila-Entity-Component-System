#ifndef SYSTEM_H
#define SYSTEM_H

#include <bitset>

#include "Component.h"
#include "ComponentExtractor.h"

namespace aq
{
	/**
	 * SystemBase
	 * base for polymorphism
	 * Do not inherit this class
	 */
	class SystemBase
	{
	protected:
		std::bitset< 64 > m_lockBits;
		bool m_enabled;

		/** 
		 * Registers a component type with the system
		 */
		template< typename Component > void addComponentType();
	public:
		SystemBase();

		/**
		 * Updates the system
		 * This method must be implemented
		 */
		virtual void update( ComponentExtractor& extractor ) = 0;

		/**
		 * Draws the contents of the system
		 * This method can be implemented if rendering is required
		 */
		virtual void draw( ComponentExtractor& extractor ) {}

		/**
		 * Makes system visible to the world
		 */
		void enable();

		/**
		 * Makes system invisible to the world
		 */
		void disable();

		/**
		 * Checks if the system is enabled
		 * if it's enabled it returns true
		 * if it isn't enabled it returns false
		 */
		bool enabled();

		/**
		 * Returns a bit set containing required components as 1's
		 * Acts as a lock so that only the requested components can be used
		 */
		std::bitset< 64 >& getLockBits();

		/**
		 * Retrieves object type ID
		 */
		virtual int getSystemType() = 0;
	};

	/**
	 * System
	 * All systems must inherit this class using CRTP
	 * ex. class MovementSystem : public System< MovementSystem >
	 */
	template< class T > class System : public SystemBase
	{
	protected:
		static int m_type;
	public:
		System() {}

		/**
		 * Retrieves class type ID
		 */
		static int systemType() { return m_type; }
		int getSystemType() { return T::m_type; }
	};

	static int nextSystemType = 0;
	template< typename T > int System< T >::m_type( nextSystemType++ );

	template< typename Component > void SystemBase::addComponentType()
	{
		m_lockBits.set( Component::type() );
	}
}
#endif // SYSTEM_H
