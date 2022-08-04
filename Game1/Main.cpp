#include "Engine.h"
#include <iostream>

//code --> preprocessor --> compiler --> (.o, .o, .o) --> link --> .exe
int add(int a, int b)
{
	return a + b;
}

constexpr int add_c(int a, int b)
{
	return a + b;
}

int main()
{
	const int i = 5;

	int i2 = add(6, 7);
	constexpr int i3 = add_c(6, 7); //compile time functions

	constexpr float degrees = math::RadtoDeg(math::Pi);

	std::cout << __FILE__ << std::endl; //FILE DIRECTORY
	std::cout << __LINE__ << std::endl; // LINE OF CODE
	std::cout << __FUNCTION__ << std::endl;// WHERE ITS CALLED

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

	//std::cout << "Hello World!" << std::endl;

	//sprite/image
	std::shared_ptr<neu::Texture> texture = std::make_shared<neu::Texture>();
	texture->Create(neu::g_renderer, "ElGato.png");


	float angel = 0;


	bool gaming = true;
	while (gaming)
	{
		//update (engine)
		neu::g_time.Tick();
		neu::g_inputSystem.Update();
		//audio
		neu::g_audioSystem.Update();

		if (neu::g_inputSystem.GetKeyDown(neu::key_escape)) gaming = false;

		angel += 90.0f * neu::g_time.deltaTime;

		//render
		neu::g_renderer.BeginFrame();
		//images
		neu::g_renderer.Draw(texture, { 600, 600 }, angel, {0.5f , 0.5f}, { 0.5f, 0.5f });
		neu::g_renderer.EndFrame();
	}
	//shut
	neu::g_audioSystem.Shutdown();
	neu::g_renderer.Shutdown();
}