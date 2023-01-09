#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include "Utilities/Containers/darray.h"
#include "MinQDefines.h"

namespace mqvk
{
	class VulkanDevice;

	struct VulkanContext
	{
		VkInstance vkInstance;
		VkSurfaceKHR vkSurface;
		darray<const char*> validationLayers;
		VkDebugUtilsMessengerEXT debugMessenger;
		VulkanDevice* vulkanDevice;
	};
	
	extern VulkanContext g_VulkanContext;
}