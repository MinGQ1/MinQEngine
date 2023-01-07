#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

namespace mqvk
{
	struct VulkanDeviceConfigurtion
	{
		bool graphicQueueRequire;
		bool presentQueueRequire;
		bool computeQueueRequire;
		bool transferQueueRequire;
	};

	struct VulkanQueueFamilyIndex
	{
		Int32 graphicsFamilyIndex;
		Int32 presentFamilyIndex;
		Int32 computeFamilyIndex;
		Int32 transferFamilyIndex;
	};

	class VulkanDevice
	{
	public:
		//Well, i found that VKInstance is actually a pointer;
		VulkanDevice(VkInstance vkInstance): m_VkInstance(vkInstance)
		{
		}

		void InitVulkanDevice();
	private:
		VkPhysicalDevice m_PhysicalDevice;
		VkDevice m_LogicalDevice;
		VkInstance m_VkInstance;
		VulkanQueueFamilyIndex m_QueueFamilyIndex;
	};
}