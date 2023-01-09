#include "VulkanDevice.h"
#include "VulkanDefines.h"
#include "Utilities/Containers/darray.h"

namespace mqvk
{
	bool VulkanDevice::CheckPhysicalDeviceSutiable(VkPhysicalDevice device, bool updateQueueIndex)
	{
#define WRITE_QUEUEFAMILYINDEX_AND_CONFIG(id, idName, queueRequireName) do {\
		familyIndices.idName = id; \
		configuration.queueRequireName = true; \
		} while (0)

		bool result = false;
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		darray<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		VulkanQueueFamilyIndex	familyIndices;
		VulkanDeviceConfiguration configuration;
		int id = 0;
		for (darray<VkQueueFamilyProperties>::iterator it = queueFamilies.begin(); it != queueFamilies.end(); it++)
		{
			VkQueueFamilyProperties& queuefamilies = *it;
			if (queuefamilies.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				WRITE_QUEUEFAMILYINDEX_AND_CONFIG(id, graphicsFamilyIndex, graphicQueueRequire);
			}
			if (queuefamilies.queueFlags & VK_QUEUE_COMPUTE_BIT)
			{
				WRITE_QUEUEFAMILYINDEX_AND_CONFIG(id, computeFamilyIndex, computeQueueRequire);
			}
			if (queuefamilies.queueFlags & VK_QUEUE_TRANSFER_BIT)
			{
				WRITE_QUEUEFAMILYINDEX_AND_CONFIG(id, transferFamilyIndex, transferQueueRequire);
			}
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, id, g_VulkanContext.vkSurface, &presentSupport);
			if (presentSupport)
			{
				WRITE_QUEUEFAMILYINDEX_AND_CONFIG(id, presentFamilyIndex, presentQueueRequire);
			}
			if (m_Configuration.QueueRequireMatch(configuration))
			{
				result = true;
				break;
			}
			id++;
		}
		return result;
	}

	VulkanDevice::VulkanDevice()
	{
	}

	VulkanDevice::VulkanDevice(VulkanDeviceConfiguration config): 
		m_Configuration(config)
	{
	}

	void VulkanDevice::InitVulkanDevice()
	{
		UInt32 phicaldeviceCount = 0;
		vkEnumeratePhysicalDevices(g_VulkanContext.vkInstance, &phicaldeviceCount, nullptr);
		if (phicaldeviceCount == 0) {
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}

		darray<VkPhysicalDevice> devices(phicaldeviceCount);
		vkEnumeratePhysicalDevices(g_VulkanContext.vkInstance, &phicaldeviceCount, devices.data());

		for (darray<VkPhysicalDevice>::iterator it = devices.begin(); it != devices.end(); it++)
		{
			if (CheckPhysicalDeviceSutiable(*it, true))
				m_PhysicalDevice = *it;
		}
	}
}