#include "Engine.h"
#include <iostream>

int main()
{
	{//int i = 10;
	//float f = 3.5f;
	//bool b = false;

	//const char* s = "LOL!";
	////std::cout << i << f << b;
	//printf("hello world %d %.2f %d %s\n", i, f, b, s);
	}

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
	neu::g_renderer.SetClearColor(neu::Color{ 21, 130, 173, 255 });

	//std::cout << "Hello World!" << std::endl;

	//sprite/image
	std::shared_ptr<neu::Texture> texture = std::make_shared<neu::Texture>();
	texture->Create(neu::g_renderer, "ElGato.png");



	bool gaming = true;
	while (gaming)
	{
		//update (engine)
		neu::g_time.Tick();
		neu::g_inputSystem.Update();
		//audio
		neu::g_audioSystem.Update();

		if (neu::g_inputSystem.GetKeyDown(neu::key_escape)) gaming = false;

		//render
		neu::g_renderer.BeginFrame();
		//images
		neu::g_renderer.Draw(texture, { 400, 300 }, 0);
		neu::g_renderer.EndFrame();
	}
	//shut
	neu::g_audioSystem.Shutdown();
	neu::g_renderer.Shutdown();
}