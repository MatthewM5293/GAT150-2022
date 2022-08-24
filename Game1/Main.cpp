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
	neu::g_physicsSystem.Initialize();
	neu::g_resourceManager.Initialize();

	neu::Engine::Instance().Register();

	//create window
	int width = 800; //800
	int height = 600; //600
	neu::g_renderer.CreateWindow("Gaming", width, height);
	neu::g_renderer.SetClearColor(neu::Color::black); //old color: neu::Color{ 21, 130, 173, 255 }

	std::shared_ptr<neu::Texture> texture = neu::g_resourceManager.Get<neu::Texture>("textures/player.png", &neu::g_renderer);
	
	//audio
	neu::g_audioSystem.AddAudio("laser", "Audio/laser_shoot.wav");

	//Create scene
	neu::Scene scene;

	rapidjson::Document document;
	bool success = neu::json::Load("level.txt", document);
	assert(success);
	scene.Read(document);
	scene.Initialize();

	float angle = 0;

	bool gaming = true;
	while (gaming)
	{
		//update (engine)
		neu::g_time.Tick();
		neu::g_inputSystem.Update();
		//audio
		neu::g_audioSystem.Update();

		//physics
		neu::g_physicsSystem.Update();

		if (neu::g_inputSystem.GetKeyDown(neu::key_escape)) gaming = false;

		//update scene
		angle += 360.0f * neu::g_time.deltaTime; //rotation
		scene.Update();

		//render
		neu::g_renderer.BeginFrame();
		
		scene.Draw(neu::g_renderer);

		neu::g_renderer.EndFrame();
	}
	scene.RemoveAll();

	//shut
	neu::g_physicsSystem.Shutdown();
	neu::g_inputSystem.Shutdown();
	neu::g_resourceManager.Shutdown();
	neu::g_audioSystem.Shutdown();
	neu::g_renderer.Shutdown();
}