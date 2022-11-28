#include "Core/Application.h"
//#include "Logger/Log.h"
#include "Core/EntryPoint.h"

class TestbedApp : public Application
{
public:
	TestbedApp()
	{

	}

	~TestbedApp()
	{

	}
};

Application* CreateApplication()
{
	return new TestbedApp();
}