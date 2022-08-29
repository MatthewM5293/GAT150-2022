#include "Engine.h"

namespace neu 
{
	InputSystem g_inputSystem;
	Renderer g_renderer;
	Time g_time;
	AudioSystem g_audioSystem;
	ResourceManager g_resourceManager;
	PhysicsSystem g_physicsSystem;
	EventManager g_eventManager;
	

	void Engine::Register()
	{
		REGISTER_CLASS(Actor); //== Factory::Instance().Register<Actor>("Actor");
		REGISTER_CLASS(AudioComponent);
		REGISTER_CLASS(ModelComponent);
		REGISTER_CLASS(CollisionComponent);
		REGISTER_CLASS(PhysicsComponent);
		REGISTER_CLASS(RBPhysicsComponent);
		REGISTER_CLASS(PlayerComponent);
		REGISTER_CLASS(SpriteComponent);
		REGISTER_CLASS(TextComponent);
		REGISTER_CLASS(TilemapComponent);
		REGISTER_CLASS(SpriteAnimComponent);
	}
}