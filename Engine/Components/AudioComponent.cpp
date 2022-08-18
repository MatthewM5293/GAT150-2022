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
	bool AudioComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool AudioComponent::Read(const rapidjson::Value& value)
	{
		return false;
	}
}
