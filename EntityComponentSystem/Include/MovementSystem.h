#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "System.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"

#include <iostream>

class MovementSystem : public System<MovementSystem>
{
public:
	MovementSystem()
	{
		addComponentType<PositionComponent>();
		addComponentType<VelocityComponent>();
	}

	void update(ComponentExtractor& extractor) override
	{
		Component<PositionComponent>::Ptr pos = extractor.getComponent<PositionComponent>();
		Component<VelocityComponent>::Ptr vel = extractor.getComponent<VelocityComponent>();

		pos->m_x += vel->m_xVel;
		pos->m_y += vel->m_yVel;

		std::cout << pos->m_x << " " << pos->m_y << std::endl;
	}
};
#endif // MOVEMENTSYSTEM_H
