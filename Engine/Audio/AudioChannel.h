#pragma once 

namespace FMOD
{
	class Channel;
}

namespace neu
{
	class AudioChannel
	{
	public:
		AudioChannel() = default;
		AudioChannel(FMOD::Channel* channel) : m_channel{ channel } {}

		bool IsPlaying();
		void Stop();

		// !! create SetPitch/GetPitch (takes float, returns float) 
		void SetPitch(float pitch);
		float GetPitch();
		// !! create SetVolume/GetVolume (takes float, returns float) 
		void SetVolume(float volume);
		float GetVolume();

	private:
		FMOD::Channel* m_channel = nullptr;
	};
}