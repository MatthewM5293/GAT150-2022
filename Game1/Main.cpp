#include "Engine.h"
#include "TheGame.h"
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
	neu::g_eventManager.Initialize();

	neu::Engine::Instance().Register();

	//create window
	int width = 800; //800
	int height = 600; //600
	neu::g_renderer.CreateWindow("Gaming", width, height);
	neu::g_renderer.SetClearColor(neu::Color::black); //old color: neu::Color{ 21, 130, 173, 255 }

	//create game
	std::unique_ptr<TheGame> game = std::make_unique<TheGame>();
	game->Initialize();

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
		neu::g_eventManager.Update();

		if (neu::g_inputSystem.GetKeyDown(neu::key_escape)) gaming = false;

		//update scene
		game->Update();

		//render
		neu::g_renderer.BeginFrame();
		
		game->Draw(neu::g_renderer);

		neu::g_renderer.EndFrame();
	}
	game->Shutdown();
	game.reset();

	neu::Factory::Instance().Shutdown();

	//shut
	neu::g_eventManager.Shutdown();
	neu::g_resourceManager.Shutdown();
	neu::g_physicsSystem.Shutdown();
	neu::g_audioSystem.Shutdown();
	neu::g_inputSystem.Shutdown();
	neu::g_renderer.Shutdown();
}