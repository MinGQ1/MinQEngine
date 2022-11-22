#pragma once

#include<AEDefines.h>
#include"MemoryTags.h"

class MemoryManager
{
public:
	MemoryManager();
	~MemoryManager();

	void* Allocate(UInt64 size, MemoryTag tag);
	void* Deallocate(void* block, UInt64, MemoryTag tag);
};