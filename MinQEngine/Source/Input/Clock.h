#pragma once
#include "AEDefines.h"

struct Clock
{
	double startTime;
	double elapsed;
};

class ClockManager
{
public:
	Clock GetClock() { return m_Clock; }
	void StartClock();
	void UpdateClock();
	void StopClock();
private:
	Clock m_Clock;
};