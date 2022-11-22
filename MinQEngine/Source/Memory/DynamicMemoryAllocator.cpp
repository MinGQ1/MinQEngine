#include "DynamicMemoryAllocator.h"
#include <ArrowEngine/Logger/Assert.h>
#include <Utilities/BitOperationUtility.h>

void* DynamicMemoryAllocator::Allocate(size_t size, size_t alignment)
{
	Assert(LOWEST_BIT_CLEAR(alignment) == 0);
	size_t alignedSize = BitRoundUp(size, alignment);
}
