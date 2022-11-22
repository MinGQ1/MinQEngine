#include "Log.h"
#include "Assert.h"
#include <AEDefines.h>
#include <string>

std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

void Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_CoreLogger = spdlog::stdout_color_mt("ArrowEngine");
	s_CoreLogger->set_level(spdlog::level::trace);
	s_ClientLogger = spdlog::stdout_color_mt("Application");
	s_ClientLogger->set_level(spdlog::level::trace);
}

void LogAssertionMsg(const char* expression, const char* message, const char* file, UInt32 line)
{
	std::string lineStr = std::to_string(line);
	AE_CORE_FATAL(message, expression,"At: File:", file, "Line:", lineStr.c_str());
}