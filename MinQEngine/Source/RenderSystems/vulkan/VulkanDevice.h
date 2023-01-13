#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include <vector>

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

	struct VulkanQueueFamilyIndices
	{
		VulkanQueueFamilyIndices()
		{
			graphicsFamilyIndex = -1;
			presentFamilyIndex = -1;
			computeFamilyIndex = -1;
			transferFamilyIndex = -1;
		}
		bool GraphicPresentShareQueue() const { return graphicsFamilyIndex == presentFamilyIndex; }
		Int32 graphicsFamilyIndex;
		Int32 presentFamilyIndex;
		Int32 computeFamilyIndex;
		Int32 transferFamilyIndex;
	};

	enum VkQueueType
	{
		kVkQueueGraphic = 0,
		kVkQueuePresent,
		kVkQueueCompute,
		kVkQueueTransfer,
		kVkQueueTypeCount
	};

	class VulkanDevice
	{
	public:
		VulkanDevice();
		VulkanDevice(VulkanDeviceConfiguration config);

		void InitVulkanDevice();
		// vk device is actually a pointer type
		VkPhysicalDevice GetPhysicalDevices() { return m_PhysicalDevice; }
		VkDevice GetLogicalDevice() { return m_LogicalDevice;};
		const VulkanQueueFamilyIndices& GetQueueFamilyIndices() const { return m_QueueFamilyIndices; }
	private:
		bool CheckPhysicalDeviceSutiable(VkPhysicalDevice device, bool updateConfig);
		VkPhysicalDevice m_PhysicalDevice;
		VkDevice m_LogicalDevice;
		VulkanQueueFamilyIndices m_QueueFamilyIndices;
		VulkanDeviceConfiguration m_Configuration;
		darray<VkQueue> m_VkQueue;

		const std::vector<const char*> m_Extension = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	};
}