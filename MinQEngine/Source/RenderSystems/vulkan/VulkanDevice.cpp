#include "Logger/Assert.h"
#include "VulkanDevice.h"
#include "VulkanDefines.h"
#include "Utilities/Containers/darray.h"
#include <set>

namespace mqvk
{
	bool VulkanDevice::CheckPhysicalDeviceSutiable(VkPhysicalDevice device, bool updateQueueIndex)
	{
#define WRITE_QUEUEFAMILYINDEX_AND_CONFIG(id, idName, queueRequireName) do {\
		familyIndices.idName = familyIndices.idName >= 0 ? familyIndices.idName : id; \
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
				if (updateQueueIndex)
				{
					m_QueueFamilyIndices = familyIndices;
				}
				break;
			}
			id++;
		}
		return result;
	}

	VulkanDevice::VulkanDevice()
	{
		m_VkQueue = darray<VkQueue>(kVkQueueTypeCount);
	}

	VulkanDevice::VulkanDevice(VulkanDeviceConfiguration config): 
		m_Configuration(config)
	{
		m_VkQueue = darray<VkQueue>(kVkQueueTypeCount);
	}

	void VulkanDevice::InitVulkanDevice()
	{
		// phick physical device
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

		//create logical device

		darray<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<UInt32> queueFamiliesSet;
		if (m_Configuration.graphicQueueRequire)	queueFamiliesSet.insert(m_QueueFamilyIndices.graphicsFamilyIndex);
		if (m_Configuration.computeQueueRequire)	queueFamiliesSet.insert(m_QueueFamilyIndices.computeFamilyIndex);
		if (m_Configuration.transferQueueRequire)	queueFamiliesSet.insert(m_QueueFamilyIndices.transferFamilyIndex);
		if (m_Configuration.presentQueueRequire)	queueFamiliesSet.insert(m_QueueFamilyIndices.presentFamilyIndex);

		float queuePriority = 1.0f;
		for (uint32_t queueFamily : queueFamiliesSet) {
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = queueCreateInfos.size();

		createInfo.pEnabledFeatures = &deviceFeatures;

		//createInfo.enabledExtensionCount = 0;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(m_Extension.size());
		createInfo.ppEnabledExtensionNames = m_Extension.data();

#if MINQ_VK_VALIDATION_LAYERS
		createInfo.enabledLayerCount = static_cast<uint32_t>(g_VulkanContext.validationLayers.size());
		createInfo.ppEnabledLayerNames = g_VulkanContext.validationLayers.data();
#else
		createInfo.enabledLayerCount = 0;
#endif

		CheckVkResult(vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_LogicalDevice));

		AssertMsg(m_VkQueue.size() == kVkQueueTypeCount, "VulkanDevice: Wrong size of vk queue");
		vkGetDeviceQueue(m_LogicalDevice, m_QueueFamilyIndices.graphicsFamilyIndex, 0, &m_VkQueue[kVkQueueGraphic]);
		vkGetDeviceQueue(m_LogicalDevice, m_QueueFamilyIndices.presentFamilyIndex, 0, &m_VkQueue[kVkQueuePresent]);
		vkGetDeviceQueue(m_LogicalDevice, m_QueueFamilyIndices.transferFamilyIndex, 0, &m_VkQueue[kVkQueueTransfer]);
		vkGetDeviceQueue(m_LogicalDevice, m_QueueFamilyIndices.computeFamilyIndex, 0, &m_VkQueue[kVkQueueCompute]);
	}
}