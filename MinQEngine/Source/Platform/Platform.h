#pragma once
#include "MinQDefines.h"
#include "Core/Window.h"

namespace Platform
{
	Window* CreateWindow(const WndProps& prop);

	double GetAbsoluteTime();

	void Allocate(UInt64 size);

	void AllocateAligned(UInt64 size, UInt64 alignment);
}



