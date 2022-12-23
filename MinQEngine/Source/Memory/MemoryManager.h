#pragma once

#include<MinQDefines.h>
#include"MemoryTags.h"

class MemoryManager
{
public:
	MemoryManager();
	~MemoryManager();

	void* Allocate(UInt64 size, MemoryTag tag);
	void Deallocate(void* block, MemoryTag tag);
	void* Reallocate(void* block, UInt64 size, MemoryTag tag);
};

MemoryManager& GetMemoryManager();