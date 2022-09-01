#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace neu 
{
	void PlayerComponent::Initialize()
	{
		CharacterComponent::Initialize();
		g_eventManager.Subscribe("EVENT_HEALTH", std::bind(&CharacterComponent::OnNotify, this, std::placeholders::_1), m_owner);
	}

	void PlayerComponent::Update()
	{
		Vector2 direction = Vector2::zero;

		float p_speed = 100;
		//input
		auto left1 = neu::g_inputSystem.GetKeyState(neu::key_left) == neu::InputSystem::KeyState::Held;
		auto left2 = neu::g_inputSystem.GetKeyState(neu::key_a) == neu::InputSystem::KeyState::Held;
		if (left1 || left2)
		{
			//m_owner->m_transform.rotation -= 180 * neu::g_time.deltaTime;
			direction = Vector2::left;
		}

		auto right1 = neu::g_inputSystem.GetKeyState(neu::key_right) == neu::InputSystem::KeyState::Held;
		auto right2 = neu::g_inputSystem.GetKeyState(neu::key_d) == neu::InputSystem::KeyState::Held;
		if (right1 || right2)
		{
			//m_owner->m_transform.rotation += 180 * neu::g_time.deltaTime;
			direction = Vector2::right;
		}

		auto up1 = neu::g_inputSystem.GetKeyState(neu::key_up) == neu::InputSystem::KeyState::Held;
		auto up2 = neu::g_inputSystem.GetKeyState(neu::key_w) == neu::InputSystem::KeyState::Held;
		if (m_groundCount > 0 && up1 || m_groundCount > 0 && up2)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				component->ApplyForce(Vector2::up * jump);
			}

		}
		
		//velocity
		Vector2 velocity;
		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			//if in the air (m_groundCount==0) then reduce force 
			float multiplier = (m_groundCount > 0) ? 1 : 0.2f;

			component->ApplyForce(direction * speed * multiplier);
			velocity = component->velocity;
		}
		
		auto animComponent = m_owner->GetComponent<SpriteAnimComponent>();
		if (animComponent)
		{
			if (velocity.x != 0) animComponent->SetFlipHorizontal(velocity.x < 0);
			if (std::fabs(velocity.x) > 0)
			{
				animComponent->SetSequence("run");
			}
			else
			{
				animComponent->SetSequence("idle");
			}
			if (std::fabs(velocity.y) != 0)
			{
				animComponent->SetSequence("jump");
			}
		}


		m_owner->m_transform.position += direction * 300 * g_time.deltaTime;

		auto down1 = neu::g_inputSystem.GetKeyState(neu::key_down) == neu::InputSystem::KeyState::Held;
		auto down2 = neu::g_inputSystem.GetKeyState(neu::key_s) == neu::InputSystem::KeyState::Held;
		//set speed (move)
		if (down1 || down2)
		{
			
		}

		if (neu::g_inputSystem.GetKeyState(key_space) == neu::InputSystem::KeyState::Pressed)
		{
			auto component = m_owner->GetComponent<AudioComponent>();
			if (component)
			{
				component->Play();
			}
		}

		//set camera
		auto camera = m_owner->GetScene()->GetActorFromName("Camera");
		if (camera) 
		{
			//camera->m_transform.position = m_owner->m_transform.position;
			camera->m_transform.position = math::Lerp(camera->m_transform.position, m_owner->m_transform.position, 2 * g_time.deltaTime);
		}
		
	}
	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		CharacterComponent::Read(value);
		READ_DATA(value, jump);
		return true;
	}

	void PlayerComponent::OnNotify(const Event& event)
	{
		//damage
		if (event.name == "EVENT_DAMAGE")
		{
			health -= std::get<float>(event.data);
			if (health <= 0)
			{
				m_owner->SetDestroy();

				Event event;
				event.name = "EVENT_PLAYER_DEAD";

				g_eventManager.Notify(event);

			}

		}
		if (event.name == "EVENT_HEAL")
		{
			health += std::get<float>(event.data);
		}
	}

	void PlayerComponent::OnCollisionEnter(Actor* other)
	{
		if (other->GetName() == "Coin")
		{
			Event event;
			event.name = "EVENT_ADD_POINTS";
			event.data = 100;

			g_eventManager.Notify(event);

			other->SetDestroy();
		}
		if (other->GetName() == "Coin")
		{
			Event event;
			event.name = "EVENT_HEAL";
			event.data = 10;

			g_eventManager.Notify(event);
		}

		if (other->GetTag() == "Enemy")
		{
			Event event;
			event.name = "EVENT_DAMAGE";
			event.data = damage;
			event.receiver = other;

			g_eventManager.Notify(event);
		}

		if (other->GetTag() == "Ground") 
		{ 
			m_groundCount++; 
		}

		
	}
	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		if (other->GetTag() == "Ground") 
		{
			m_groundCount--; 
		}
	}
}
