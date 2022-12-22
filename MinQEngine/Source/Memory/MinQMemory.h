#pragma once
#include "MemoryManager.h"

inline void RealDelete(void* ptr, MemoryTag tag)
{

}

#define MINQ_NEW(type, tag)	new(GetMemoryManager().Allocate(sizeof(type), tag)) type
#define MINQ_DELETE(ptr, tag) { ;GetMemoryManager().Deallocate();}