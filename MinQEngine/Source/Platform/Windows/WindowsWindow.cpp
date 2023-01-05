#include"WindowsWindow.h"
#include "GLFW/glfw3.h"
#include <Platform/Platform.h>

WindowsWindow::WindowsWindow(const WndProps& props)
{
	m_AdditionData.width = props.width;
	m_AdditionData.height = props.height;
	m_AdditionData.eventMgr = new EventManager();

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


Window* Platform::CreatePlatformWindow(const WndProps& props)
{
	return new WindowsWindow(props);
}


