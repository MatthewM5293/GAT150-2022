#include "Engine.h"
#include <iostream>

int main()
{
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");

	rapidjson::Document document;
	bool success = neu::json::Load("json.txt", document);
	assert(success);

	std::string str;
	neu::json::Get(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	neu::json::Get(document, "boolean", b);
	std::cout << b << std::endl;

	int i1;
	neu::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	neu::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;

	float f;
	neu::json::Get(document, "float", f);
	std::cout << f << std::endl;

	neu::Vector2 v2;
	neu::json::Get(document, "vector2", v2);
	std::cout << v2 << std::endl;

	neu::Color color;
	neu::json::Get(document, "color", color);
	std::cout << color << std::endl;

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
	//font
	//auto font = neu::g_resourceManager.Get<neu::Font>("fonts/arcadeclassic.ttf", 10);

	/*std::shared_ptr<neu::Model> model = std::make_shared<neu::Model>();
	model->Create("Models/Player.txt");*/


	//audio
	neu::g_audioSystem.AddAudio("laser", "Audio/laser_shoot.wav");

	//Create actors
	neu::Scene scene;

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
	neu::g_inputSystem.Shutdown();
	neu::g_resourceManager.Shutdown();
	neu::g_audioSystem.Shutdown();
	neu::g_renderer.Shutdown();
}