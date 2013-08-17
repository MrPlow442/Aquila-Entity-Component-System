Entity-Component-System
=======================

First attempt at creating an Entity Component System.

Using the system:

`````C++
	aq::World world;
	
	aq::Entity& ent = world.createEntity();
	ent.addComponent(new PositionComponent(0,0));
	ent.addComponent(new VelocityComponent(1,2));
	
	world.addSystem( new MovementSystem() );
	
	for(auto i = 0u; i < 10; ++i)
	{
		world.update();
	}
`````

Creating a component:

`````C++
	struct PositionComponent : public Component<PositionComponent>
	{
	public:
		float m_x, m_y;
		PositionComponent(float x, float y) : m_x(x), m_y(y) {}
	};
`````

Creating a system:

`````C++
	class MovementSystem : public System<MovementSystem>
	{
	public:
		MovementSystem()
		{
			registerComponentType<PositionComponent>();
			registerComponentType<VelocityComponent>();
		}
	
		void update(ComponentProvider& extractor) override
		{
			Component<PositionComponent>::Ptr pos = extractor.getComponent<PositionComponent>();
			Component<VelocityComponent>::Ptr vel = extractor.getComponent<VelocityComponent>();
	
			pos->m_x += vel->m_xVel;
			pos->m_y += vel->m_yVel;
	
			std::cout << pos->m_x << " " << pos->m_y << std::endl;
		}
	};
`````
