#pragma once

#include "Logger/Log.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

inline void CheckVkResult(VkResult result)
{
	if (result != VK_SUCCESS)
	{
		// TODO: throw a exception
	}
}

