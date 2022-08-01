#include "InputSystem.h"
#include <SDL.h>
#include <iostream>

namespace neu 
{
	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_up = SDL_SCANCODE_UP;
	const uint32_t key_down = SDL_SCANCODE_DOWN;
	const uint32_t key_left = SDL_SCANCODE_LEFT;
	const uint32_t key_right = SDL_SCANCODE_RIGHT;
	const uint32_t key_escape = SDL_SCANCODE_ESCAPE;

	//WASD
	const uint32_t key_w = SDL_SCANCODE_W;
	const uint32_t key_a = SDL_SCANCODE_A;
	const uint32_t key_s = SDL_SCANCODE_S;
	const uint32_t key_d = SDL_SCANCODE_D;

	const uint32_t key_1 = SDL_SCANCODE_1;
	const uint32_t key_2 = SDL_SCANCODE_2;
	const uint32_t key_3 = SDL_SCANCODE_3;

	//mouse
	const uint32_t button_left = 0;
	const uint32_t button_middle = 1;
	const uint32_t button_right = 2;

	void InputSystem::Initialize()
	{
		const uint8_t* keyboardState = SDL_GetKeyboardState(&m_numKeys);

		m_keyboardState.resize(m_numKeys);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		m_prevKeyboardState = m_keyboardState;
	}
	
	void InputSystem::Shutdown()
	{
		//

	}
	
	void InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		//save previous keyboard state
		m_prevKeyboardState = m_keyboardState;

		//get current keyboard state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		//std::cout << (bool)m_keyboardState[SDL_SCANCODE_SPACE] << std::endl;
		/*for (auto state : m_keyboardState)
		{
			std::cout << (bool)state << std::endl;
		}
		std::cout << std::endl;
		*/

		//Mouse
		m_prevMouseButtonState = m_mouseButtonState;
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = neu::Vector2{ x , y };
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML] 
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML] 
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [0RML] 



	}

	InputSystem::KeyState InputSystem::GetKeyState(uint32_t key)
	{
		KeyState keyState = KeyState::Idle;

		bool keyDown = GetKeyDown(key);
		bool prevKeyDown = GetPreviousKeyDown(key);

		if (keyDown && prevKeyDown) keyState = KeyState::Held;
		if (keyDown && !prevKeyDown) keyState = KeyState::Pressed;
		if (!keyDown && prevKeyDown) keyState = KeyState::Released;
		if (!keyDown && !prevKeyDown) keyState = KeyState::Idle;
		// set the keyState if buttonDown (true) and prevButtonDown (true) 
		// fill in the remaining states 

		return keyState;
	}


	InputSystem::KeyState InputSystem::GetButtonState(uint32_t button)
	{
		KeyState buttonState = KeyState::Idle;

		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPreviousButtonDown(button);

		if (buttonDown && prevButtonDown) buttonState = KeyState::Held;
		if (buttonDown && !prevButtonDown) buttonState = KeyState::Pressed;
		if (!buttonDown && prevButtonDown) buttonState = KeyState::Released;
		if (!buttonDown && !prevButtonDown) buttonState = KeyState::Idle;
		// set the keyState if buttonDown (true) and prevButtonDown (true) 
		// fill in the remaining states 

		return buttonState;
	}

}