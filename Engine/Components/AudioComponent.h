#pragma once
#include "Framework/Component.h"


namespace neu
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent() = default;

		void Update() override;
	
		void Play();
		void Stop();

	public:
		std::string m_soundname;
		bool playOnAwake = false;
		float m_pitch = 1;
		bool m_loop = false;
	};
}