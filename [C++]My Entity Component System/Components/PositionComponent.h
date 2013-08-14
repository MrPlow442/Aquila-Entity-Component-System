#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "Component.h"

struct PositionComponent : public Component<PositionComponent>
{
public:
	float m_x, m_y;
	PositionComponent(float x, float y) : m_x(x), m_y(y) {}
};
#endif // POSITIONCOMPONENT_H
