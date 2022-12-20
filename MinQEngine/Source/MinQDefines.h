#pragma once

#include "Configuration/BuildConfig.h"
#include<cstdint>

typedef ::uint8_t UInt8;
typedef ::uint16_t UInt16;
typedef ::uint32_t UInt32;
typedef ::uint64_t UInt64;
typedef ::int8_t Int8;
typedef ::int16_t Int16;
typedef ::int32_t Int32;
typedef ::int64_t Int64;

#define TURE 1
#define FALSE 0
#define NULL 0
#define STATIC_ASSERT static_assert

#define MINQ_NEW
#define MEMORY_TAG(tag) kMem##tag
#define DEFAULT_MEM_ALIGNMENT 16