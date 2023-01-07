#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include "Utilities/Containers/darray.h"
#include "MinQDefines.h"

class VulkanDevice;

struct VulkanDeviceDesc
{
	Int32 graphicsQueueIndex;
	Int32 presentQueueIndex;
	Int32 transferQueueIndex;

	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkQueue transferQueue;
};

struct VulkanContext
{
	VkInstance vkInstance;	
	VkSurfaceKHR vkSurface;
	darray<const char*> validationLayers;
	VkDebugUtilsMessengerEXT debugMessenger;
	VulkanDevice* vulkanDevice;
};