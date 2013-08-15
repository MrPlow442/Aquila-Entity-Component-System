#ifndef SYSTEM_H
#define SYSTEM_H

#include <bitset>

#include "Component.h"
#include "ComponentExtractor.h"

namespace aq
{
	class SystemBase
	{
	protected:
		std::bitset< 64 > m_lockBits;
		bool m_enabled;
		template< typename Component > void addComponentType();
	public:
		SystemBase();
		virtual void update( ComponentExtractor& extractor ) = 0;
		virtual void draw( ComponentExtractor& extractor ) {}

		void enable();
		void disable();
		bool enabled();

		std::bitset< 64 >& getLockBits();
		virtual int getSystemType() = 0;
	};

	template< class T > class System : public SystemBase
	{
	protected:
		static int m_type;
	public:
		System() {}
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
