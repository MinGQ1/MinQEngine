#pragma once
#include "RenderSystems/RenderSystem.h"
#include "VulkanContext.h"
#include "Utilities/Containers/darray.h"

struct GLFWwindow;

class VulkanRenderSystem : public RenderSystem
{
public:
	// TODO: remove this
	void SetGlfwWindow(GLFWwindow* window) { m_GlfwWindow = window; }

	void Initialize() override;
private:
	//static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
	void CreateInstance(const char* appName);
	void CreateSurface();
	void SetupDebugMessenger();
	void PickPhysicalDevice();
	VulkanContext m_VulkanContext;
	GLFWwindow* m_GlfwWindow;
};