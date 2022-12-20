#include "MemoryManager.h"
#include "Platform/Platform.h"

void* MemoryManager::Allocate(UInt64 size, MemoryTag tag)
{
	// TODO: 1.USE ALLOCATOR
	//		 2.PROFILING MEM
	Platform::AllocateAligned(size, DEFAULT_MEM_ALIGNMENT);
	return nullptr;
}
