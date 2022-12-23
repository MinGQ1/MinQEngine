#include "MemoryManager.h"
#include "Platform/Platform.h"

void* MemoryManager::Allocate(UInt64 size, MemoryTag tag)
{
	// TODO: 1.USE ALLOCATOR
	//		 2.PROFILING MEM
	Platform::AllocateAligned(size, DEFAULT_MEM_ALIGNMENT);
	return nullptr;
}

void MemoryManager::Deallocate(void* block, MemoryTag tag)
{
	Platform::DeallocateAligned(block);
}

void* MemoryManager::Reallocate(void* block,UInt64 size, MemoryTag tag)
{
	return Platform::ReallocateAligned(block, size, tag);
}

MemoryManager g_MemoryManager;

MemoryManager& GetMemoryManager()
{
	return g_MemoryManager;
}
