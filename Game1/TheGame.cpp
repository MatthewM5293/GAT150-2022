#include "TheGame.h"
#include "GameComponents/EnemyComponent.h"
#include "Engine.h"

void TheGame::Initialize()
{
	REGISTER_CLASS(EnemyComponent);

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

	neu::g_eventManager.Subscribe("EVENT_ADD_POINTS", std::bind(&TheGame::OnNotify, this, std::placeholders::_1));
	neu::g_eventManager.Subscribe("EVENT_PLAYER_DEAD", std::bind(&TheGame::OnNotify, this, std::placeholders::_1));
	neu::g_eventManager.Subscribe("EVENT_PLAYER_HEAL", std::bind(&TheGame::OnNotify, this, std::placeholders::_1));
}

void TheGame::Shutdown()
{
	m_scene->RemoveAll();
}

void TheGame::Update()
{
	switch (m_gameState)
	{
	case TheGame::gameState::titleScreen:
		if (neu::g_inputSystem.GetKeyState(neu::key_space) == neu::InputSystem::Pressed)
		{
			m_scene->GetActorFromName("Title")->SetActive(false);

			m_gameState = gameState::startLevel;
		}
		break;
	case TheGame::gameState::startLevel:
		m_scene->GetActorFromName("Title2")->SetActive(false);

		//coins
		for (int i = 0; i < 10; i++)
		{
			auto actor = neu::Factory::Instance().Create<neu::Actor>("Coin");
			actor->m_transform.position = { neu::randomf(0, 800), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		//ENEMIES
		for (int i = 0; i < 3; i++)
		{
			auto actor = neu::Factory::Instance().Create<neu::Actor>("Ghost");
			actor->m_transform.position = { neu::randomf(0, 800), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		{
			auto actor = neu::Factory::Instance().Create<neu::Actor>("Player");
			actor->m_transform.position = { 400.0f, 250.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}

		m_lives = 3;
		m_gameState = gameState::game;

		break;
	case TheGame::gameState::game:
	{
		m_scene->GetActorFromName("Title2")->SetActive(false);

		auto actor = m_scene->GetActorFromName("Score");
		auto component = actor->GetComponent<neu::TextComponent>();
		if (component)
		{
			component->SetText(std::to_string(m_score));
		}
	}
	{
		auto actor = m_scene->GetActorFromName("Health");
		auto component = actor->GetComponent<neu::TextComponent>();

		auto player = m_scene->GetActorFromName("Player");
		auto playerComponent = player->GetComponent<neu::PlayerComponent>();
		if (playerComponent)
		{
			component->SetText(std::to_string((int)playerComponent->health));
		}
	}
		break;
	case TheGame::gameState::playerDead:
		m_stateTimer -= neu::g_time.deltaTime;
		if (m_stateTimer <= 0)
		{
			m_gameState = gameState::startLevel;
			m_gameState = (m_lives > 0) ? gameState::startLevel : gameState::gameOver;
		}
		break;
	case TheGame::gameState::gameOver:
		m_scene->GetActorFromName("Title2")->SetActive(true);

		break;
	default:
		break;
	}

	//spawn timers, spawns coins/enemies every few seconds (based on miliseconds) 1 second = 1000 miliseconds
	m_coinTimer -= neu::g_time.deltaTime;

	if (m_coinTimer <= 0)
	{
		//coins
		for (int i = 0; i < 10; i++)
		{
			auto actor = neu::Factory::Instance().Create<neu::Actor>("Coin");
			actor->m_transform.position = { neu::randomf(0, 800), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		m_coinTimer = neu::random(20000, 200000);
	}

	m_enemyTimer -= neu::g_time.deltaTime;
	if (m_enemyTimer <= 0)
	{
		//ENEMIES
		for (int i = 0; i < 3; i++)
		{
			auto actor = neu::Factory::Instance().Create<neu::Actor>("Ghost");
			actor->m_transform.position = { neu::randomf(0, 800), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		m_enemyTimer = neu::random(10000, 100000);
	}


	m_scene->Update();

}

void TheGame::Draw(neu::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void TheGame::OnAddPoints(const neu::Event& event)
{
	AddPoints(std::get<int>(event.data));
}

void TheGame::OnAddHP(const neu::Event& event)
{
	AddHP(10);
}

void TheGame::OnPlayerDead(const neu::Event& event)
{
	m_gameState = gameState::playerDead;
	m_lives--; //lives
	m_stateTimer = 3;
}

void TheGame::OnNotify(const neu::Event& event)
{
	if (event.name == "EVENT_ADD_POINTS")
	{
		AddPoints(std::get<int>(event.data));
		AddHP(10);
	}
	if (event.name == "EVENT_PLAYER_DEAD")
	{
		m_gameState = gameState::playerDead;
		m_lives--; //lives
		m_stateTimer = 3;
	}
}
