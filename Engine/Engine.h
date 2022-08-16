#pragma once

#include "Serialization/Json.h" 

#include "Core/Memory.h"
#include "Core/File.h"
#include "Core/Time.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"

#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Framework/Factory.h"
#include "Framework/Singleton.h"

#include "Components/PlayerComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/ModelComponent.h"

#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Resource/ResourceManager.h"

#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Texture.h"
#include "Renderer/Model.h"

#include <memory>


namespace neu 
{
	extern InputSystem g_inputSystem;
	extern Renderer g_renderer;
	extern Time g_time;
	extern AudioSystem g_audioSystem;
	extern ResourceManager g_resourceManager;

	class Engine : public Singleton<Engine>
	{
	public:
		void Register();
		
	};
}