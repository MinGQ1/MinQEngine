#pragma once

#ifdef  MQ_PLATFORM_WINDOWS

extern Application* CreateApplication();

int main(int argc, char** argv)
{
	auto app = CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // AE_PLATFORM_WINDOWS
