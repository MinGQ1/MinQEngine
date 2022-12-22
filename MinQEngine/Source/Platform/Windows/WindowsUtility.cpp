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

void Deallowcate(void* block)
{
	free(block);
}

void DeallowcateAligned(void* block)
{
	_aligned_free(block);
}