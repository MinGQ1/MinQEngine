#pragma once
#include "MemoryManager.h"

#define MINQ_NEW(type, tag)	new(GetMemoryManager().Allocate(sizeof(type), tag)) type
#define MINQ_DELETE(ptr, type, tag) { if(ptr) (ptr)->~type(); GetMemoryManager().Deallocate(ptr, tag);}