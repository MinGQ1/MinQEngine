#include "VulkanDevice.h"
#include "VulkanDefines.h"
#include "Utilities/Containers/darray.h"

namespace mqvk
{
	static bool CheckPhysicalDeviceSutiable(VkPhysicalDevice device)
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		darray<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		VulkanQueueFamilyIndex	familyIndices;
		for (darray<VkQueueFamilyProperties>::iterator it = queueFamilies.begin(); it != queueFamilies.end(); it++)
		{

		}
	}

	void VulkanDevice::InitVulkanDevice()
	{
		UInt32 phicaldeviceCount = 0;
		vkEnumeratePhysicalDevices(m_VkInstance, &phicaldeviceCount, nullptr);
		if (phicaldeviceCount == 0) {
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}

		darray<VkPhysicalDevice> devices(phicaldeviceCount);
		vkEnumeratePhysicalDevices(m_VkInstance, &phicaldeviceCount, devices.data());

		for (darray<VkPhysicalDevice>::iterator it = devices.begin(); it != devices.end(); it++)
		{
			if (CheckPhysicalDeviceSutiable(*it))
				m_PhysicalDevice = *it;
		}
	}
}