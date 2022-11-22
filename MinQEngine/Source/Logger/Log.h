#pragma once

#include <MinQDefines.h>
#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"

class AE_API Log
{
public:
	static void Init();
		
	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
private:
	static std::shared_ptr<spdlog::logger> s_CoreLogger;
	static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

// Core Log
#define AE_CORE_TRACE(...) Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AE_CORE_INFO(...) Log::GetCoreLogger()->info(__VA_ARGS__)
#define AE_CORE_WARN(...) Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AE_CORE_ERROR(...) Log::GetCoreLogger()->error(__VA_ARGS__)
#define AE_CORE_FATAL(...) Log::GetCoreLogger()->critical(__VA_ARGS__)

// App log
//#define AE_TRACE(...) Log::GetClientLogger()->trace(__VA_ARGS__)
//#define AE_INFO(...) Log::GetClientLogger()->info(__VA_ARGS__)
//#define AE_WARN(...) Log::GetClientLogger()->warn(__VA_ARGS__)
//#define AE_ERROR(...) Log::GetClientLogger()->error(__VA_ARGS__)
//#define AE_FATAL(...) Log::GetClientLogger()->critical(__VA_ARGS__)