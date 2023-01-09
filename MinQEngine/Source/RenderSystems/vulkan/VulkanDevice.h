#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

namespace mqvk
{
	struct VulkanDeviceConfiguration
	{
		VulkanDeviceConfiguration():
			graphicQueueRequire(true),
			presentQueueRequire(true),
			computeQueueRequire(true),
			transferQueueRequire(true)
		{
		}

		bool graphicQueueRequire;
		bool presentQueueRequire;
		bool computeQueueRequire;
		bool transferQueueRequire;

		bool QueueRequireMatch(VulkanDeviceConfiguration& other)
		{
			bool result = true;
			result &= other.graphicQueueRequire = graphicQueueRequire;
			result &= other.presentQueueRequire = presentQueueRequire;
			result &= other.computeQueueRequire = computeQueueRequire;
			result &= other.transferQueueRequire = transferQueueRequire;
			return result;
		}
	};

	struct VulkanQueueFamilyIndex
	{
		VulkanQueueFamilyIndex()
		{
			graphicsFamilyIndex = -1;
			presentFamilyIndex = -1;
			computeFamilyIndex = -1;
			transferFamilyIndex = -1;
		}
		Int32 graphicsFamilyIndex;
		Int32 presentFamilyIndex;
		Int32 computeFamilyIndex;
		Int32 transferFamilyIndex;
	};

	class VulkanDevice
	{
	public:
		VulkanDevice();
		VulkanDevice(VulkanDeviceConfiguration config);

		void InitVulkanDevice();
	private:
		bool CheckPhysicalDeviceSutiable(VkPhysicalDevice device, bool updateConfig);
		VkPhysicalDevice m_PhysicalDevice;
		VkDevice m_LogicalDevice;
		VulkanQueueFamilyIndex m_QueueFamilyIndex;
		VulkanDeviceConfiguration m_Configuration;	
	};
}