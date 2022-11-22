#pragma once

class MemoryAllocator
{
public:
	virtual void* Allocate(size_t size, size_t alignment) = 0;
	virtual void* Deallocate(void* block, size_t size) = 0;
};