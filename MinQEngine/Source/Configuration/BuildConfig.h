#pragma once

#ifdef  MQ_PLATFORM_WINDOWS
#ifdef MQ_BUILD_DLL
#define MQ_API __declspec(dllexport)
#else
#define MQ_API __declspec(dllimport)
#endif // DEBUG
#else
//#error Platform not support!s
#define MQ_API
#endif //  MQ_PLATFORM_WINDOWS

// assertion
#ifdef ASSERTIONS_ON
#undef ASSERTIONS_ON
#endif

#define ASSERTIONS_ON 1