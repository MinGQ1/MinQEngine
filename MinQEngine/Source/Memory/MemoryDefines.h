#pragma once

#define DEFAULT_ALIGNMENT 16

#define ALIGNED_MALLOC(size, align) _aligned_malloc(size, align)

typedef void* MemoryPool;