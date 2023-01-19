#pragma once
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include <map>

namespace mqvk
{
	struct VulkanRenderPassDesc
	{
		struct Compare
		{
			bool operator()(const VulkanRenderPassDesc& lhs, const VulkanRenderPassDesc& rhs);
		};
	};

	class VulkanRenderPassCache
	{
	public:
		VkRenderPass GetRenderPass(const VulkanRenderPassDesc& passDesc);
	private:
		std::map<VulkanRenderPassDesc, VkRenderPass, VulkanRenderPassDesc::Compare> m_RenderPassCache;
	};


}
