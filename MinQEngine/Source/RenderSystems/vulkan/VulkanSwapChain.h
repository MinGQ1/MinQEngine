#pragma once
#include "VulkanDefines.h"
#include "Utilities/Containers/darray.h"

namespace mqvk
{
	struct VulkanSwapChainConfiguration
	{
		VulkanSwapChainConfiguration()
		{
			surfaceFormat.colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
			surfaceFormat.format = VK_FORMAT_R8G8B8A8_SRGB;
			presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
		}
		VkSurfaceFormatKHR surfaceFormat;
		VkPresentModeKHR presentMode;
	};

	class VulkanSwapChain
	{
	public:
		VulkanSwapChain();
		VulkanSwapChain(VulkanSwapChainConfiguration config);
		void CreateSwapChain();

	private:
		void QuerySwapChainSupport();
		VkSwapchainKHR m_SwapChain;
		darray<VkSurfaceFormatKHR> m_SurfaceFormatSupport;
		darray<VkPresentModeKHR> m_PresentModeSupport;
		VkSurfaceCapabilitiesKHR m_SurfaceCapabilities;
		VulkanSwapChainConfiguration m_Configuration;
		VkExtent2D m_Extent;
	};
}