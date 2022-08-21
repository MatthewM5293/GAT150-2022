#pragma once 
#include "box2d/b2_world.h"
#include <memory> 

namespace neu
{
	class PhysicsSystem
	{
	public:
		PhysicsSystem() = default;
		~PhysicsSystem() = default;

		void Initialize();
		void Shutdown();

		void Update();

	private:
		std::unique_ptr<b2World> world;
	};
}