#include"WindowsWindow.h"
#include "GLFW/glfw3.h"
#include <Platform/Platform.h>

WindowsWindow::WindowsWindow(const ArrowEngine::WndProps& props)
{
	m_AdditionData.width = props.width;
	m_AdditionData.height = props.height;
	m_AdditionData.eventMgr = new ArrowEngine::EventManager();

	int success = glfwInit();
	m_Window = glfwCreateWindow(m_AdditionData.width, m_AdditionData.height, props.title, NULL, NULL);
}

void WindowsWindow::Update()
{
	glfwPollEvents();
}

void WindowsWindow::Destroy()
{
	glfwDestroyWindow(m_Window);

	glfwTerminate();
}

WindowsWindow::~WindowsWindow()
{
	delete m_AdditionData.eventMgr;
}


ArrowEngine::Window* CreatePlatformWindow(const ArrowEngine::WndProps& props)
{
	return new WindowsWindow(props);
}


