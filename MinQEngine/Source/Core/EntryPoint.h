#pragma once
#include "Logger/Log.h"

#ifdef  MQ_PLATFORM_WINDOWS

extern Application* CreateApplication();

int main(int argc, char** argv)
{
	// Init Log before application because we want to log imformation during application creation;
	Log::Init();
	auto app = CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // AE_PLATFORM_WINDOWS
