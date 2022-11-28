#pragma once
#include <MinQDefines.h>

#ifdef ASSERTIONS_ON

#ifdef MQ_PLATFORM_WINDOWS
#include <intrin.h>
#	define MQ__ASSERT_IMPL(test, msg) do{ \
	LogAssertionMsg(#test, msg, __FILE__, __LINE__);\
	__debugbreak();\
} while(0)
#else
//TODO: Other platform
#	define ARROW__ASSERT_IMPL(test, msg) (void*)0
#endif // AE_PLATFORM_WINDOWS

#else
#	define MQ__ASSERT_IMPL(test, msg) (void*)0
#endif // ASSERTIONS_ON

MQ_API void LogAssertionMsg(const char* expression, const char* message, const char* file, UInt32 line);

#define Assert(test) MQ__ASSERT_IMPL(test, "")
#define AssertMsg(test, msg)	MQ__ASSERT_IMPL(test, msg)