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
	neu::g_resourceManager.Initialize();

	neu::Engine::Instance().Register();

	//create window
	int width = 1200; //800
	int height = 1000; //600
	neu::g_renderer.CreateWindow("Gaming", width, height);
	neu::g_renderer.SetClearColor(neu::Color::black); //old color: neu::Color{ 21, 130, 173, 255 }

	//sprite/image
	//std::shared_ptr<neu::Texture> texture = std::make_shared<neu::Texture>();
	//texture->Create(neu::g_renderer, "Textures/Enemy.png");
	std::shared_ptr<neu::Texture> texture = neu::g_resourceManager.Get<neu::Texture>("textures/player.png", &neu::g_renderer);

	/*std::shared_ptr<neu::Model> model = std::make_shared<neu::Model>();
	model->Create("Models/Player.txt");*/


	//audio
	neu::g_audioSystem.AddAudio("laser", "Audio/laser_shoot.wav");

	//Create actors
	neu::Scene scene;
							//position, angle, scale
	neu::Transform transform{ {500, 500}, 0, {3, 3 } };
	//std::unique_ptr<neu::Actor> actor = std::make_unique<neu::Actor>(transform);
	std::unique_ptr<neu::Actor> actor = neu::Factory::Instance().Create<neu::Actor>("Actor");
	actor->m_transform = transform;
	std::unique_ptr<neu::Component> pComponent = neu::Factory::Instance().Create<neu::Component>("PlayerComponent");
	actor->AddComponent(std::move(pComponent));
	
	//Player Sprite
	/*std::unique_ptr<neu::SpriteComponent> sComponent = std::make_unique<neu::SpriteComponent>();
	sComponent->m_texture = texture;
	actor->AddComponent(std::move(sComponent));*/

	//model
	std::unique_ptr<neu::ModelComponent> mComponent = std::make_unique<neu::ModelComponent>();
	mComponent->m_model = neu::g_resourceManager.Get<neu::Model>("Models/Player.txt");
	actor->AddComponent(std::move(mComponent));

	std::unique_ptr<neu::AudioComponent> aComponent = std::make_unique<neu::AudioComponent>();
	aComponent->m_soundname = "laser";
	actor->AddComponent(std::move(aComponent));

	std::unique_ptr<neu::Component> phComponent = neu::Factory::Instance().Create<neu::Component>("PhysicsComponent");
	actor->AddComponent(std::move(phComponent));

	//child actor
	neu::Transform transformC{ {40, 30}, 0, {1, 1 } }; //relative of parent
	std::unique_ptr<neu::Actor> child = std::make_unique<neu::Actor>(transformC);

	std::unique_ptr<neu::ModelComponent> mComponentC = std::make_unique<neu::ModelComponent>();
	mComponentC->m_model = neu::g_resourceManager.Get<neu::Model>("Models/Player.txt");
	child->AddComponent(std::move(mComponentC));

	actor->AddChild(std::move(child));

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
		angle += 360.0f * neu::g_time.deltaTime; //rotation
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