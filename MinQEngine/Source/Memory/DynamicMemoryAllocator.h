#pragma once
#include "MemoryAllocator.h"
#include "MemoryDefines.h"

class DynamicMemoryAllocator: MemoryAllocator
{
public:
	void* Allocate(size_t size, size_t alignment) override;
};