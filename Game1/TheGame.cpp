#include "TheGame.h"
#include "Engine.h"

void TheGame::Initialize()
{
	m_scene = std::make_unique<neu::Scene>();

	rapidjson::Document document;

	std::vector<std::string> sceneNames = { "scenes/prefabs.txt", "scenes/level.txt", "scenes/tilemap.txt"};

	for (auto& sceneName : sceneNames)
	{
		bool success = neu::json::Load(sceneName, document);
		if (!success)
		{
			LOG("could not load scene %s", sceneName.c_str());
			continue;
		}
		//assert(success);
		m_scene->Read(document);
	}
	m_scene->Initialize();

	//coins
	for (int i = 0; i < 10; i++)
	{
		auto actor = neu::Factory::Instance().Create<neu::Actor>("Coin");
		actor->m_transform.position = { neu::randomf(0, 800), 100.0f };
		actor->Initialize();

		m_scene->Add(std::move(actor));
	}
}

void TheGame::Shutdown()
{
	m_scene->RemoveAll();
}

void TheGame::Update()
{
	m_scene->Update();

}

void TheGame::Draw(neu::Renderer& renderer)
{
	m_scene->Draw(renderer);
}
