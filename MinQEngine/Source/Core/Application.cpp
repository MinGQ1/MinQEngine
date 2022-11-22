#include "Application.h"
#include "Platform/Platform.h"
#include <ArrowEngine/Logger/Log.h>

Application* Application::s_Instance = NULL;

Application::Application(): m_ShouldQuit(false), m_Window(NULL)
{
	if (s_Instance)
		AE_CORE_FATAL("Already has application instance");
	s_Instance = this;
	m_ImguiLayer = new ImguiLayer();
	REGISTER_UPDATABLE_LAYER(kImguiLayer, m_ImguiLayer);
}

Application::~Application()
{
}

void Application::Run()
{		
	m_Window = CreatePlatformWindow(WndProps(1920, 1080, "Arrow Engine"));
	while (!m_ShouldQuit)
	{
		m_Window->Update();
		CALL_UPDATABLE_LAYER(kImguiLayer);
	}

	m_Window->Destroy();
}
