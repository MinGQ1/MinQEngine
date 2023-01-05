#pragma once
#include "MinQDefines.h"
#include "Core/Window.h"

namespace Platform
{
	Window* CreatePlatformWindow(const WndProps& prop);

	double GetAbsoluteTime();
	void* Allocate(UInt64 size);
	void* AllocateAligned(UInt64 size, UInt64 alignment);
	void Deallocate(void* block);
	void DeallocateAligned(void* block);
	void* Reallocate(void* block, UInt64 size);
	void* ReallocateAligned(void* block, UInt64 size, UInt64 alignment);
}



