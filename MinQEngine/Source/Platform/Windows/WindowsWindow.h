#pragma once

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include "ArrowEngine/Core/Window.h"
#include "GLFW/glfw3.h"

class WindowsWindow : public ArrowEngine::Window
{
public:
	WindowsWindow(const ArrowEngine::WndProps& props);
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
		ArrowEngine::EventManager* eventMgr;
	};

	WndAdditionData m_AdditionData;
	GLFWwindow* m_Window;
};


