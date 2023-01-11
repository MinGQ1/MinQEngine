#pragma once
#include "VulkanDefines.h"
#include "Utilities/Containers/darray.h"

namespace mqvk
{
	class VulkanSwapChain
	{
	public:
		void CreateSwapChain();

	private:
		void QuerySwapChainSupport();
		VkSwapchainKHR m_SwapChain;
		darray<VkSurfaceFormatKHR> m_SupportSurfaceFormat;
		darray<VkPresentModeKHR> m_SupportPresentMode;
		VkSurfaceCapabilitiesKHR m_SurfaceCapabilities;
	};
}