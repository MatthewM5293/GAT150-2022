#include "TheGame.h"
#include "GameComponents/EnemyComponent.h"
#include "Engine.h"

void TheGame::Initialize()
{
	REGISTER_CLASS(EnemyComponent);

	//add audio here
	neu::g_audioSystem.AddAudio("coin", "audio/coin.wav");
	neu::g_audioSystem.AddAudio("hit", "audio/hit_hurt.wav");
	neu::g_audioSystem.AddAudio("hurt", "audio/hit.wav");
	neu::g_audioSystem.AddAudio("jump", "audio/jump.wav");
	neu::g_audioSystem.AddAudio("explosion", "audio/explosion.wav");
	neu::g_audioSystem.AddAudio("shoot", "audio/Laser_Shoot.wav");

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
	//neu::g_eventManager.Subscribe("EVENT_HEAL", std::bind(&TheGame::OnNotify, this, std::placeholders::_1));
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

		////coins
		//for (int i = 0; i < 10; i++)
		//{
		//	auto actor = neu::Factory::Instance().Create<neu::Actor>("Coin");
		//	actor->m_transform.position = { neu::randomf(0, 1200), 100.0f };
		//	actor->Initialize();

		//	m_scene->Add(std::move(actor));
		//}
		////ENEMIES
		//for (int i = 0; i < 3; i++)
		//{
		//	auto actor = neu::Factory::Instance().Create<neu::Actor>("Ghost");
		//	actor->m_transform.position = { neu::randomf(0, 1200), 100.0f };
		//	actor->Initialize();

		//	m_scene->Add(std::move(actor));
		//}

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

		//score display
		auto actor = m_scene->GetActorFromName("Score");
		auto component = actor->GetComponent<neu::TextComponent>();
		if (component)
		{
			component->SetText("Score: " + std::to_string(m_score));
		}
	}
	//HP display
	{
		auto actor = m_scene->GetActorFromName("Health");
		auto component = actor->GetComponent<neu::TextComponent>();

		auto player = m_scene->GetActorFromName("Player");
		auto playerComponent = player->GetComponent<neu::PlayerComponent>();
		if (playerComponent)
		{
			component->SetText("HP: " + std::to_string((int)playerComponent->health));
		}
	}
	//Lives display (needs to update)
	{
		auto actor = m_scene->GetActorFromName("Lives");
		auto component = actor->GetComponent<neu::TextComponent>();

		auto player = m_scene->GetActorFromName("Player");
		auto playerComponent = player->GetComponent<neu::PlayerComponent>();
		if (playerComponent)
		{
			component->SetText("Lives: " + std::to_string((int)m_lives));
		}
	}
		break;
	case TheGame::gameState::playerDead:
		m_stateTimer -= neu::g_time.deltaTime;
		if (m_stateTimer <= 0)
		{

			m_gameState = (m_lives > 0) ? gameState::startLevel : gameState::gameOver;
			
			m_gameState = gameState::startLevel;
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
		for (int i = 0; i < 5; i++)
		{
			auto actor = neu::Factory::Instance().Create<neu::Actor>("Coin");
			actor->m_transform.position = { neu::randomf(0, 1600), 300.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		m_coinTimer = neu::random(1, 20);
	}

	m_enemyTimer -= neu::g_time.deltaTime;
	if (m_enemyTimer <= 0)
	{
		//ENEMIES
		for (int i = 0; i < 2; i++)
		{
			auto actor = neu::Factory::Instance().Create<neu::Actor>("Ghost");
			actor->m_transform.position = { neu::randomf(0, 1200), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		
		//ENEMIES
		for (int i = 0; i < 1; i++)
		{
			auto actor = neu::Factory::Instance().Create<neu::Actor>("Ogre");
			actor->m_transform.position = { neu::randomf(0, 1200), 350.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		//ENEMIES
		for (int i = 0; i < 2; i++)
		{
			auto actor = neu::Factory::Instance().Create<neu::Actor>("Bat");
			actor->m_transform.position = { neu::randomf(0, 1200), 100.0f };
			actor->Initialize();

			m_scene->Add(std::move(actor));
		}
		m_enemyTimer = neu::random(10, 40);
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
	}
	if (event.name == "EVENT_PLAYER_DEAD")
	{
		m_gameState = gameState::playerDead;
		m_lives--; //lives
		m_stateTimer = 3;
	}
}
