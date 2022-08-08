#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace neu 
{
	void PlayerComponent::Update()
	{
		Vector2 direction = Vector2::zero;

		float p_speed = 100;
		//input
		auto left1 = neu::g_inputSystem.GetKeyState(neu::key_left) == neu::InputSystem::KeyState::Held;
		auto left2 = neu::g_inputSystem.GetKeyState(neu::key_a) == neu::InputSystem::KeyState::Held;
		if (left1 || left2)
		{
			//m_owner->m_transform.rotation -= math::TwoPi * neu::g_time.deltaTime;
			//m_owner->m_transform.position.x -= p_speed * neu::g_time.deltaTime;
			//direction = Vector2::left;
			m_owner->m_transform.rotation -= 180 * neu::g_time.deltaTime;
		}

		auto right1 = neu::g_inputSystem.GetKeyState(neu::key_right) == neu::InputSystem::KeyState::Held;
		auto right2 = neu::g_inputSystem.GetKeyState(neu::key_d) == neu::InputSystem::KeyState::Held;
		if (right1 || right2)
		{
			//m_owner->m_transform.rotation += math::TwoPi * neu::g_time.deltaTime;
			//m_owner->m_transform.position.x += p_speed * neu::g_time.deltaTime;
			//direction = Vector2::right;
			m_owner->m_transform.rotation += 180 * neu::g_time.deltaTime;
		}

		auto up1 = neu::g_inputSystem.GetKeyState(neu::key_up) == neu::InputSystem::KeyState::Held;
		auto up2 = neu::g_inputSystem.GetKeyState(neu::key_w) == neu::InputSystem::KeyState::Held;
		//set speed (move)
		float thrust = 0;
		if (up1 || up2)
		{
			thrust = 500;
			
			
			//m_owner->m_transform.position.y -= p_speed * neu::g_time.deltaTime;
			//direction = Vector2::up;

		}

		auto component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			//thrust force
			Vector2 force = Vector2::Rotate({ 1, 0 }, math::DegToRad(m_owner->m_transform.rotation)) * thrust;
			component->ApplyForce(force);

			//gravitational force
			force = (Vector2{ 200, 200 } - m_owner->m_transform.position).Normalized() * 60.0f;
			component->ApplyForce(force);
		}

		m_owner->m_transform.position += direction * 300 * g_time.deltaTime;

		auto down1 = neu::g_inputSystem.GetKeyState(neu::key_down) == neu::InputSystem::KeyState::Held;
		auto down2 = neu::g_inputSystem.GetKeyState(neu::key_s) == neu::InputSystem::KeyState::Held;
		//set speed (move)
		if (down1 || down2)
		{
			//m_owner->m_transform.position.y += p_speed * neu::g_time.deltaTime;
			//direction += Vector2::down * 100;
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
}
