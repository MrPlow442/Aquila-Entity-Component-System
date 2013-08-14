#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

struct ComponentBase
{
public:
	virtual int getType() const = 0;
};

template<class T> struct Component : public ComponentBase
{
private:
	static int m_type;
public:
	typedef std::shared_ptr<T> Ptr;
	static int type() { return m_type; }
	int getType() const { return T::m_type; }
};

static int nextType = 0;
template<typename T> int Component<T>::m_type(nextType++);
#endif // COMPONENT_H
