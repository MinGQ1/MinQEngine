#pragma once

#ifdef  MQ_PLATFORM_WINDOWS

extern ArrowEngine::Application* ArrowEngine::CreateApplication();

int main(int argc, char** argv)
{
	Log::Init();
	AE_CORE_WARN("Hello Warn!");
	AE_CORE_ERROR("Hello Error!");
	auto app = ArrowEngine::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // AE_PLATFORM_WINDOWS
