#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include "Utilities/Containers/darray.h"
#include "MinQDefines.h"

struct GLFWwindow;

namespace mqvk
{
	class VulkanDevice;
	class VulkanSwapChain;

	struct VulkanContext
	{
		VkInstance vkInstance;
		VkSurfaceKHR vkSurface;
		darray<const char*> validationLayers;
		VkDebugUtilsMessengerEXT debugMessenger;
		VulkanDevice* vulkanDevice;
		VulkanSwapChain* SwapChain;
		GLFWwindow* glfwWindow;
	};
	
	extern VulkanContext g_VulkanContext;
}