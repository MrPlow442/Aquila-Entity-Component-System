#include "../Aquila/Include/System.h"
#include "../Aquila/Include/World.h"

namespace aq
{
	SystemBase::SystemBase() :
		m_enabled(true) {}


	std::bitset<64>& SystemBase::getLockBits()
	{
		return m_lockBits;
	}

	void SystemBase::enable()
	{
		m_enabled = true;
	}

	void SystemBase::disable()
	{
		m_enabled = false;
	}

	bool SystemBase::enabled()
	{
		return m_enabled;
	}
}
