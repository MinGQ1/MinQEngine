#include <Platform/Platform.h>

double Platform::GetAbsoluteTime()
{
	return 0;
}

void* Platform::Allocate(UInt64 size)
{
	return malloc(size);
}

void* Platform::AllocateAligned(UInt64 size, UInt64 alignment)
{
	return _aligned_malloc(size, alignment);
}

void Platform::Deallocate(void* block)
{
	free(block);
}

void Platform::DeallocateAligned(void* block)
{
	_aligned_free(block);
}

void* Platform::Reallocate(void* block, UInt64 size)
{
	return realloc(block, size);
}

void* Platform::ReallocateAligned(void* block, UInt64 size, UInt64 alignment)
{
	return _aligned_realloc(block, size, alignment);
}