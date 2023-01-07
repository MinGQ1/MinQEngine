#include "Application.h"
#include "Platform/Platform.h"
#include "Logger/Log.h"
#include "Memory/MinQMemory.h"
#include "RenderSystems/vulkan//VulkanRenderSystem.h"

Application* Application::s_Instance = NULL;

Application::Application(): m_ShouldQuit(false), m_Window(NULL)
{
	if (s_Instance)
		LogFatal("Already has application instance");
	s_Instance = this;
	m_ImguiLayer = new ImguiLayer();
	REGISTER_UPDATABLE_LAYER(kImguiLayer, m_ImguiLayer);
}

Application::~Application()
{
}

static void InitRenderSystem()
{

}

void Application::Run()
{		
	// TODO: make window size&name configurable.
	m_Window = Platform::CreatePlatformWindow(WndProps(1920, 1080, "MinQ Engine"));

	m_RenderSystem = MINQ_NEW(VulkanRenderSystem, kMemRenderSystem)((GLFWwindow*)m_Window->GetRealWindowPtr());
	m_RenderSystem->Initialize();
	while (!m_ShouldQuit)
	{
		m_Window->Update();
		//CALL_UPDATABLE_LAYER(kImguiLayer);
	}

	m_Window->Destroy();
}
