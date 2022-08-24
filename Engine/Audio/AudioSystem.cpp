#include "AudioSystem.h" 
#include "Core/Logger.h"
#include <fmod.hpp> 

namespace neu
{
	void AudioSystem::Initialize()
	{
		FMOD::System_Create(&m_fmodSystem);

		void* extradriverdata = nullptr;
		m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	}

	void AudioSystem::Shutdown()
	{
		// !! use range based for-loop to iterate through m_sounds, call release on each element 
		for (auto& sounds : m_sounds)
		{
			sounds.second->release();
		}

		// !! call clear() on m_sounds to remove all elements 
		m_sounds.clear();
		// !! call close() on the fmod system
		m_fmodSystem->close();
		// !! call release() on the fmod system 
		m_fmodSystem->release();
	}

	void AudioSystem::Update()
	{
		// !! call update() on the fmod system 
		m_fmodSystem->update();
	}

	void AudioSystem::AddAudio(const std::string& name, const std::string& filename)
	{
		if (m_sounds.find(name) == m_sounds.end())
		{
			FMOD::Sound* sound = nullptr;
			m_fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);

			if (sound == nullptr)
			{
				LOG("Error creating sound %s.", filename.c_str());
			}

			m_sounds[name] = sound;
		}
	}

	AudioChannel AudioSystem::PlayAudio(const std::string& name, float volume, float pitch, bool loop)
	{
		// find sound in map 
		auto iter = m_sounds.find(name);
		// if sound key not found in map (iter == end()), return default channel 
		if (iter == m_sounds.end())
		{
			LOG("Error could not find sound %s.", name.c_str());
			return AudioChannel{};
		}

		// get sound pointer from iterator 
		FMOD::Sound* sound = iter->second;
		FMOD_MODE mode = (loop) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		sound->setMode(mode);

		// play sound, sets the pointer to the channel it is playing in 
		FMOD::Channel* channel;
		m_fmodSystem->playSound(sound, 0, false, &channel);
		channel->setVolume(volume);
		channel->setPitch(pitch);
		channel->setPaused(false);

		// return audio channel with channel pointer set 
		return AudioChannel{ channel };
	}
}