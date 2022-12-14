#include "Clock.h"
#include "Platform/Platform.h"

void ClockManager::StartClock()
{
	m_Clock.startTime = Platform::GetAbsoluteTime();
	m_Clock.elapsed = 0;
}

void ClockManager::UpdateClock()
{
	if (m_Clock.startTime > 0)
	{
		m_Clock.elapsed = Platform::GetAbsoluteTime() - m_Clock.startTime;
	}
}

void ClockManager::StopClock()
{
	m_Clock.startTime = 0;
}
