#pragma once
#include "RenderSystems/RenderSystem.h"
#include "VulkanContext.h"
#include "Utilities/Containers/darray.h"

struct GLFWwindow;

class VulkanRenderSystem : public RenderSystem
{
public:
	explicit VulkanRenderSystem(GLFWwindow* window)
	{
		m_GlfwWindow = window;
	}
	// TODO: remove this

	void Initialize() override;
private:
	//static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
	void CreateInstance(const char* appName);
	void CreateSurface();
	void SetupDebugMessenger();
	void CreateVulkanDevice();

	GLFWwindow* m_GlfwWindow;
};