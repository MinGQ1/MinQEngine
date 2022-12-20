#pragma once

#include "Logger/Log.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

// TODO: only enable in develop build
#define MINQ_VK_VALIDATION_LAYERS 1

inline void CheckVkResult(VkResult result)
{
	if (result != VK_SUCCESS)
	{
		// TODO: throw a exception
	}
}

