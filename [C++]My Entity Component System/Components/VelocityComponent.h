#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H

#include "Component.h"

struct VelocityComponent : public Component<VelocityComponent>
{
public:
	float m_xVel, m_yVel;
	VelocityComponent(float xVel, float yVel) : m_xVel(xVel), m_yVel(yVel) {}
};
#endif // VELOCITYCOMPONENT_H
