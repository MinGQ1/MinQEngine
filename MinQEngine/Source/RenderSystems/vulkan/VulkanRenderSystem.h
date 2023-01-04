#pragma once

#include "RenderSystems/RenderSystem.h"
#include "VulkanContext.h"
#include "Utilities/Containers/darray.h"

class VulkanRenderSystem : public RenderSystem
{
public:
	explicit VulkanRenderSystem(GLFWwindow* glfwWindow): m_GlfwWindow(glfwWindow)
	{
	}

	void Initialize() override;
private:
	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
	void CreateInstance(const char* appName);
	void CreateSurface();
	void SetupDebugMessenger();
	VulkanContext m_VulkanContext;
	GLFWwindow* m_GlfwWindow;
};