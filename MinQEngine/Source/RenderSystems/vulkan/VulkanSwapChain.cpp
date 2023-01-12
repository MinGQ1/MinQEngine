#include "VulkanSwapChain.h"
#include "VulkanDevice.h"
#include "VulkanDefines.h"
#include "glfw/glfw3.h"

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

	static void CheckSurface(darray<VkSurfaceFormatKHR>& availableFormats, VulkanSwapChainConfiguration& config)
	{
		bool surfaceFormatFind = false;
		for (darray<VkSurfaceFormatKHR>::iterator it = availableFormats.begin(); it != availableFormats.end(); it++)
		{
			if ((*it).format == config.surfaceFormat.format && (*it).colorSpace == config.surfaceFormat.colorSpace) {
				surfaceFormatFind = true;
			}
		}
		if (!surfaceFormatFind)
		{
			LogFatal("SwapChain:vulkan surface format not support");
		}
	}

	static void CheckSwapPresentMode(darray<VkPresentModeKHR>& presentModeSupport, VulkanSwapChainConfiguration& config) {
		bool presentModeFind =false;
		for (darray<VkPresentModeKHR>::iterator it = presentModeSupport.begin(); it != presentModeSupport.end(); it++) {
			if ((*it) == config.presentMode) {
				presentModeFind = true;
			}
		}

		if (!presentModeFind)
		{
			LogFatal("SwapChain:vulkan present mode not support");
		}
	}

	void InitExtent()
	{

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
		CheckSurface(m_SurfaceFormatSupport, m_Configuration);
		CheckSwapPresentMode(m_PresentModeSupport, m_Configuration);
		
		if (m_SurfaceCapabilities.currentExtent.width != UINT32_MAX) {
			m_Extent = m_SurfaceCapabilities.currentExtent;
		}
		else {
			int width, height;
			glfwGetFramebufferSize(g_VulkanContext.glfwWindow, &width, &height);

			m_Extent = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};

			m_Extent.width = std::max(m_SurfaceCapabilities.minImageExtent.width, std::min(m_SurfaceCapabilities.maxImageExtent.width, m_Extent.width));
			m_Extent.height = std::max(m_SurfaceCapabilities.minImageExtent.height, std::min(m_SurfaceCapabilities.maxImageExtent.height, m_Extent.height));
		}


		uint32_t imageCount = m_SurfaceCapabilities.minImageCount + 1;
		if (m_SurfaceCapabilities.maxImageCount > 0 && imageCount > m_SurfaceCapabilities.maxImageCount) {
			imageCount = m_SurfaceCapabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = g_VulkanContext.vkSurface;

		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = m_Configuration.surfaceFormat.format;
		createInfo.imageColorSpace = m_Configuration.surfaceFormat.colorSpace;
		createInfo.imageExtent = m_Extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		if (indices.graphicsFamily != indices.presentFamily) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0; // Optional
			createInfo.pQueueFamilyIndices = nullptr; // Optional
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(m_Device, &createInfo, nullptr, &m_SwapChain) != VK_SUCCESS) {
			throw std::runtime_error("failed to create swap chain!");
		}

		vkGetSwapchainImagesKHR(m_Device, m_SwapChain, &imageCount, nullptr);
		m_SwapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(m_Device, m_SwapChain, &imageCount, m_SwapChainImages.data());
		m_SwapChainImageFormat = surfaceFormat.format;
		m_SwapChainExtent = extent;
	}
}
