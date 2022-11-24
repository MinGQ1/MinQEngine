#pragma once

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include "Core/Window.h"
#include "GLFW/glfw3.h"

class WindowsWindow : public Window
{
public:
	WindowsWindow(const WndProps& props);
	virtual ~WindowsWindow();

	UInt32 GetWidth() override { return m_AdditionData.width; }
	UInt32 GetHeight() override { return m_AdditionData.height; }
	void Update() override;
	void Destroy() override;
private:
	struct WndAdditionData
	{
		UInt32 height;
		UInt32 width;
		EventManager* eventMgr;
	};

	WndAdditionData m_AdditionData;
	GLFWwindow* m_Window;
};


