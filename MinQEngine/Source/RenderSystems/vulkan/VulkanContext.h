#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include "Utilities/Containers/darray.h"

struct VulkanContext
{
	VkInstance vkInstance;	
	VkSurfaceKHR vkSurface;
	darray<const char*> validationLayers;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkPhysicalDevice physicalDevice
};