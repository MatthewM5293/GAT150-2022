#include "Engine.h"
#include <iostream>

int main()
{
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	//initilize engine
	neu::g_renderer.Initialize();
	neu::g_inputSystem.Initialize();
	neu::g_audioSystem.Initialize();

	//create window
	int width = 1200;
	int height = 1000;
	neu::g_renderer.CreateWindow("Gaming", width, height);
	neu::g_renderer.SetClearColor(neu::Color::black); //old color: neu::Color{ 21, 130, 173, 255 }

	//sprite/image
	std::shared_ptr<neu::Texture> texture = std::make_shared<neu::Texture>();
	texture->Create(neu::g_renderer, "Textures/Enemy.png");
	//audio
	neu::g_audioSystem.AddAudio("laser", "Audio/laser_shoot.wav");

	//Create actors
	neu::Scene scene;

							//position, angle, scale
	neu::Transform transform{ {400, 400}, 0, {1, 1 } };
	std::unique_ptr<neu::Actor> actor = std::make_unique<neu::Actor>(transform);
	std::unique_ptr<neu::PlayerComponent> pComponent = std::make_unique<neu::PlayerComponent>();
	actor->AddComponent(std::move(pComponent));
	
	std::unique_ptr<neu::SpriteComponent> sComponent = std::make_unique<neu::SpriteComponent>();
	sComponent->m_texture = texture;
	actor->AddComponent(std::move(sComponent));

	std::unique_ptr<neu::AudioComponent> aComponent = std::make_unique<neu::AudioComponent>();
	aComponent->m_soundname = "laser";
	actor->AddComponent(std::move(aComponent));

	std::unique_ptr<neu::PhysicsComponent> phComponent = std::make_unique<neu::PhysicsComponent>();
	actor->AddComponent(std::move(phComponent));

	scene.Add(std::move(actor));

	float angle = 0;

	bool gaming = true;
	while (gaming)
	{
		//update (engine)
		neu::g_time.Tick();
		neu::g_inputSystem.Update();
		//audio
		neu::g_audioSystem.Update();

		if (neu::g_inputSystem.GetKeyDown(neu::key_escape)) gaming = false;

		//update scene
		//angle += 90.0f * neu::g_time.deltaTime;
		scene.Update();

		//render
		neu::g_renderer.BeginFrame();
		
		scene.Draw(neu::g_renderer);
		//images (raw)
		//neu::g_renderer.Draw(texture, { 600, 600 }, angle, {0.5f , 0.5f}, { 0.5f, 0.5f });

		neu::g_renderer.EndFrame();
	}
	//shut
	neu::g_audioSystem.Shutdown();
	neu::g_renderer.Shutdown();
}