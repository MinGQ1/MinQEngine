#include "VulkanSwapChain.h"
#include "VulkanDevice.h"

namespace mqvk
{
	void VulkanSwapChain::QuerySwapChainSupport()
	{
		VkPhysicalDevice device = g_VulkanContext.vulkanDevice->GetPhysicalDevices(); 

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, g_VulkanContext.vkSurface, &m_SurfaceCapabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, g_VulkanContext.vkSurface, &formatCount, nullptr);

		if (formatCount != 0) {
			m_SurfaceFormatSupport.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, g_VulkanContext.vkSurface, &formatCount, m_SurfaceFormatSupport.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, g_VulkanContext.vkSurface, &presentModeCount, nullptr);

		if (presentModeCount != 0) {
			m_PresentModeSupport.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, g_VulkanContext.vkSurface, &presentModeCount, m_PresentModeSupport.data());
		}
	}

	VulkanSwapChain::VulkanSwapChain()
	{
	}

	VulkanSwapChain::VulkanSwapChain(VulkanSwapChainConfiguration config):
		m_Configuration(config)
	{
	}

	void VulkanSwapChain::CreateSwapChain()
	{
		QuerySwapChainSupport();
	}
}
