#include"Timer.h"

void Timer::Start()
{
	m_start = systemClock::now();
}

milliseconds Timer::Stop() const
{
	return std::chrono::duration_cast<milliseconds>(systemClock::now() - m_start);
}