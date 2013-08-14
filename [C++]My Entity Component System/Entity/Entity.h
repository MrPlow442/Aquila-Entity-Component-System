#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <bitset>
#include <unordered_map>
#include <type_traits>
#include <stdexcept>

class ComponentExtractor;

struct ComponentBase;

typedef std::shared_ptr< ComponentBase > BaseComponentPtr;

class Entity
{
private:
	unsigned int m_id;
	std::unordered_map< unsigned int, BaseComponentPtr > m_componentMap;
	std::bitset<64> m_keyBits;
public:
	Entity(unsigned int id);
	~Entity();

	std::bitset<64>& getKeyBits();

	void addComponent(ComponentBase* component);
	ComponentExtractor getRelevantComponents( std::bitset<64>& lockBits );
	template<typename T> typename std::shared_ptr<T>& getComponent();
	template<typename T> void disableComponent();
	template<typename T> void enableComponent();
	template<typename T> void removeComponent();

	unsigned int getId();
};

template<typename T> typename std::shared_ptr<T>& Entity::getComponent()
{
	static_assert(std::is_base_of< ComponentBase, T >::value, "Supplied Type is not derived from Component");
	try
	{
		return std::static_pointer_cast<T>( m_componentMap.at( T::type() ) );
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "Component doesn't exist" << std::endl;
		return nullptr;
	}
}

template<typename T> void Entity::disableComponent()
{
	static_assert(std::is_base_of< ComponentBase, T >::value, "Supplied Type is not derived from Component");
	m_keyBits.reset(T::type());
}

template<typename T> void Entity::enableComponent()
{
	static_assert(std::is_base_of< ComponentBase, T >::value, "Supplied Type is not derived from Component");
	if(m_componentMap.find(T::type()) != m_componentMap.end())
		m_keyBits.set(T::type());
}

template<typename T> void Entity::removeComponent()
{
	static_assert(std::is_base_of< ComponentBase, T >::value, "Supplied Type is not derived from Component");
	m_componentMap.erase(T::type());
	m_keyBits.reset(T::type());
}
#endif // ENTITY_H