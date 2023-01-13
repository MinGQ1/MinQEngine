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

	void VulkanSwapChain::CreateImageViews()
	{
		VkDevice logicDevice = g_VulkanContext.vulkanDevice->GetLogicalDevice();
		m_ImageViews.resize(m_Images.size());

		for (size_t i = 0; i < m_Images.size(); i++)
		{
			VkImageViewCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = m_Images[i];
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = m_ImageFormat;
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			CheckVkResult(vkCreateImageView(logicDevice, &createInfo, nullptr, &m_ImageViews[i]), "Vulkan Swapchain£ºFailed to create image views!");
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

		VulkanDevice* vulkanDevice = g_VulkanContext.vulkanDevice;
		const VulkanQueueFamilyIndices& queueFamilyIndices = vulkanDevice->GetQueueFamilyIndices();
		uint32_t graphicAndPresentId[] = { queueFamilyIndices.graphicsFamilyIndex, queueFamilyIndices.presentFamilyIndex};

		if (!queueFamilyIndices.GraphicPresentShareQueue()) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = graphicAndPresentId;
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0; // Optional
			createInfo.pQueueFamilyIndices = nullptr; // Optional
		}

		createInfo.preTransform = m_SurfaceCapabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = m_Configuration.presentMode;
		createInfo.clipped = VK_TRUE;

		createInfo.oldSwapchain = VK_NULL_HANDLE;

		CheckVkResult(vkCreateSwapchainKHR(vulkanDevice->GetLogicalDevice(), &createInfo, nullptr, &m_SwapChain));


		vkGetSwapchainImagesKHR(vulkanDevice->GetLogicalDevice(), m_SwapChain, &imageCount, nullptr);
		m_Images.resize(imageCount);
		vkGetSwapchainImagesKHR(vulkanDevice->GetLogicalDevice(), m_SwapChain, &imageCount, m_Images.data());
		m_ImageFormat = m_Configuration.surfaceFormat.format;
	}
}
