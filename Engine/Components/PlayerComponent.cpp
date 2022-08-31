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

		//velocity
		Vector2 velocity;
		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(direction * speed);
			velocity = component->velocity;
		}

		auto up1 = neu::g_inputSystem.GetKeyState(neu::key_up) == neu::InputSystem::KeyState::Held;
		auto up2 = neu::g_inputSystem.GetKeyState(neu::key_w) == neu::InputSystem::KeyState::Held;
		if (up1 || up2)
		{
			auto component = m_owner->GetComponent<PhysicsComponent>();
			if (component)
			{
				component->ApplyForce(Vector2::up * speed);
			}

		}
		auto renderComponent = m_owner->GetComponent<RenderComponent>();
		if (renderComponent)
		{
			if (velocity.x != 0) renderComponent->SetFlipHorizontal(velocity.x < 0);
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

		//rotating
		bool rReset = neu::g_inputSystem.GetButtonState(neu::button_middle) == neu::InputSystem::KeyState::Held;
		if (rReset)
		{
			m_owner->m_transform.rotation = 0;
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
			std::cout << health << std::endl;
			if (health <= 0)
			{
				//player dead
			}

		}

		//heal
		if (event.name == "EVENT_HEALTH")
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

		if (other->GetTag() == "Enemy")
		{
			Event event;
			event.name = "EVENT_DAMAGE";
			event.data = damage;
			event.receiver = other;

			g_eventManager.Notify(event);
		}

		
	}
	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		
	}
}
