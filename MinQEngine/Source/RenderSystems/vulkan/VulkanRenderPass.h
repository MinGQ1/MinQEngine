#pragma once
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

namespace mqvk
{
	struct VulkanRenderPassDesc
	{
		struct Compare
		{
			bool operator()(const VulkanRenderPassDesc& lhs, const VulkanRenderPassDesc& rhs);
		};
	};

	struct VulkanRenderPass
	{
		VulkanRenderPassDesc desc;
		VkRenderPass realRenderPass;
	};


}
