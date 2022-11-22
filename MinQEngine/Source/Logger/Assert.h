#pragma once
#include <AEDefines.h>

#ifdef ASSERTIONS_ON

#ifdef AE_PLATFORM_WINDOWS
#include <intrin.h>
#	define ARROW__ASSERT_IMPL(test, msg) \
{\
	LogAssertionMsg(#test, msg, __FILE__, __LINE__);
	__debugbreak();\
}\
#else
//TODO: Other platform
#	define ARROW__ASSERT_IMPL(test, msg) (void*)0
#endif // AE_PLATFORM_WINDOWS

#else
#	define ARROW__ASSERT_IMPL(test, msg) (void*)0
#endif // ASSERTIONS_ON

AE_API void LogAssertionMsg(const char* expression, const char* message, const char* file, UInt32 line);

#define Assert(test) ARROW__ASSERT_IMPL(test, "")
#define AssertMsg(test, msg)	ARROW__ASSERT_IMPL(test, msg)