#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace neu 
{
	void PlayerComponent::Update()
	{
		//std::cout << "playa\n";
		//update transform with input
		//add controls here (up down left right)
		float p_speed = 100;
		//input
		auto left1 = neu::g_inputSystem.GetKeyState(neu::key_left) == neu::InputSystem::KeyState::Held;
		auto left2 = neu::g_inputSystem.GetKeyState(neu::key_a) == neu::InputSystem::KeyState::Held;
		if (left1 || left2)
		{
			//m_owner->m_transform.rotation -= math::TwoPi * neu::g_time.deltaTime;
			m_owner->m_transform.position.x -= p_speed * neu::g_time.deltaTime;
		}

		auto right1 = neu::g_inputSystem.GetKeyState(neu::key_right) == neu::InputSystem::KeyState::Held;
		auto right2 = neu::g_inputSystem.GetKeyState(neu::key_d) == neu::InputSystem::KeyState::Held;
		if (right1 || right2)
		{
			//m_owner->m_transform.rotation += math::TwoPi * neu::g_time.deltaTime;
			m_owner->m_transform.position.x += p_speed * neu::g_time.deltaTime;
		}

		auto up1 = neu::g_inputSystem.GetKeyState(neu::key_up) == neu::InputSystem::KeyState::Held;
		auto up2 = neu::g_inputSystem.GetKeyState(neu::key_w) == neu::InputSystem::KeyState::Held;
		//set speed (move)
		if (up1 || up2)
		{
			m_owner->m_transform.position.y -= p_speed * neu::g_time.deltaTime;
		}

		auto down1 = neu::g_inputSystem.GetKeyState(neu::key_down) == neu::InputSystem::KeyState::Held;
		auto down2 = neu::g_inputSystem.GetKeyState(neu::key_s) == neu::InputSystem::KeyState::Held;
		//set speed (move)
		if (down1 || down2)
		{
			m_owner->m_transform.position.y += p_speed * neu::g_time.deltaTime;
		}

		//rotating
		bool rLeft = neu::g_inputSystem.GetButtonState(neu::button_left) == neu::InputSystem::KeyState::Held;
		bool rReset = neu::g_inputSystem.GetButtonState(neu::button_middle) == neu::InputSystem::KeyState::Held;
		bool rRight = neu::g_inputSystem.GetButtonState(neu::button_right) == neu::InputSystem::KeyState::Held;
		if (rLeft)
		{
			m_owner->m_transform.rotation -= math::TwoPi * neu::g_time.deltaTime;
		}
		if (rRight)
		{
			m_owner->m_transform.rotation += math::TwoPi * neu::g_time.deltaTime;
		}
		if (rReset)
		{
			m_owner->m_transform.rotation = 0;
		}
	}
}
