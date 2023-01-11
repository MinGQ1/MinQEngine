#pragma once
#include "VulkanDefines.h"
#include "Utilities/Containers/darray.h"

namespace mqvk
{
	struct VulkanSwapChainConfiguration
	{

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
	};
}