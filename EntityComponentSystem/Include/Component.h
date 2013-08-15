#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
/**
 * ComponentBase 
 * Base for polymorphism
 */
struct ComponentBase
{
public:
	/**
	 * Retrieves an integer representing a Type ID for a component
	 */
	virtual unsigned int getType() const = 0;
};

/**
* Component
* The actual component class
* All components must inherit this class using CRTP 
* ex. struct PositionComponent : Component<PositionComponent>
*/
template<class T> struct Component : public ComponentBase
{
private:
	static unsigned int m_type;
public:
	typedef std::shared_ptr<T> Ptr;

	/**
	 * Retrieves class type ID
	 */
	static unsigned int type() { return m_type; }

	/**
	 * Retrieves object type ID
	 */
	unsigned int getType() const { return T::m_type; }
};

static unsigned int nextType = 0;
template<typename T> unsigned int Component<T>::m_type(nextType++);
#endif // COMPONENT_H
