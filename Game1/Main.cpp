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
	neu::g_renderer.SetClearColor(neu::Color{ 0, 0, 0, 255 });

	std::cout << "Hello World!" << std::endl;

	bool gaming = true;
	while (gaming)
	{
		//update (engine)
		neu::g_time.Tick();
		neu::g_inputSystem.Update();
		//audio
		neu::g_audioSystem.Update();

		if (neu::g_inputSystem.GetKeyDown(neu::key_escape)) gaming = true;

		//render
		neu::g_renderer.BeginFrame();
		neu::g_renderer.EndFrame();
	}
	//shut
	neu::g_audioSystem.Shutdown();
	neu::g_renderer.Shutdown();
}