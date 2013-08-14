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

//Output:
//1 2
//2 4
//3 6
//4 8
//5 10
//6 12
//7 14
//8 16
//9 18
//10 20
