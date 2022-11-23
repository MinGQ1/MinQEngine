#pragma once

#ifdef  AE_PLATFORM_WINDOWS
	#ifdef AE_BUILD_DLL
		#define AE_API __declspec(dllexport)
	#else
		#define AE_API __declspec(dllimport)
	#endif // DEBUG
#else
	//#error Platform not support!s
	#define AE_API
#endif //  AE_PLATFORM_WINDOWS
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

#define MEMORY_TAG(tag) kMem##tag