#include "AudioComponent.h"
#include "Engine.h"

namespace neu 
{
	void AudioComponent::Update()
	{
	}

	void AudioComponent::Play()
	{
		g_audioSystem.PlayAudio(m_soundname, m_loop);
	}

	void AudioComponent::Stop()
	{
	}
}
