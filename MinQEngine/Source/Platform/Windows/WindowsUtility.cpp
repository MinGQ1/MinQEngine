#include <Platform/Platform.h>

using namespace Platform;

double GetAbsoluteTime()
{
	return 0;
}

void* Allocate(UInt64 size)
{
	return malloc(size);
}

void* AllocateAligned(UInt64 size, UInt64 alignment)
{
	return _aligned_malloc(size, alignment);
}

void Deallocate(void* block)
{
	free(block);
}

void DeallocateAligned(void* block)
{
	_aligned_free(block);
}

void* Reallocate(void* block, UInt64 size)
{
	return realloc(block, size);
}

void* ReallocateAligned(void* block, UInt64 size, UInt64 alignment)
{
	return _aligned_realloc(block, size, alignment);
}