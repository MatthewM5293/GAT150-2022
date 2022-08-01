#include "Time.h"

namespace neu
{
	void neu::Time::Tick()
	{
		clock_duration duration = clock::now() - m_startTimePoint;

		time = duration.count() / (float)clock_duration::period::den;

		duration = clock::now() - m_frameTimePoint;
		deltaTime = duration.count() / (float)clock_duration::period::den;

		m_frameTimePoint = clock::now();
	}
}
