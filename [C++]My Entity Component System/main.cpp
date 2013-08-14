#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Systems/MovementSystem.h"
#include "World.h"

int main() 
{
	World world;

	Entity& ent = world.createEntity();
	ent.addComponent(new PositionComponent(0,0));
	ent.addComponent(new VelocityComponent(1,2));

	world.createSystem<MovementSystem>();

	for(auto i = 0u; i < 10; ++i)
	{
		world.update();
	}

	return 0;
}
