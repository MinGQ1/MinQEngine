#include "VulkanRenderSystem.h"
#include "VulkanDefines.h"
#include "Logger/Log.h"
#include "glfw/glfw3.h"
#include "VulkanDevice.h"
#include "VulkanSwapChain.h"

static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageTypes,
	const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
	void* userData) {
	switch (messageSeverity) {
	default:
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
		LogError(callbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
		LogWarn(callbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
		LogInfo(callbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
		LogTrace(callbackData->pMessage);
		break;
	}
	return VK_FALSE;
}

static std::vector<const char*> GetRequiredExtensions()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#if MINQ_VK_VALIDATION_LAYERS
	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

	return extensions;
}

void VulkanRenderSystem::Initialize()
{
	CreateInstance("MinQVK");
	CreateSurface();
	SetupDebugMessenger();
	CreateVulkanDevice();
	CreateSwapChain();
}

void VulkanRenderSystem::CreateInstance(const char* appName)
{
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = appName;
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "MinQEngine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_3;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = GetRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

	mqvk::g_VulkanContext.validationLayers.push_back("VK_LAYER_KHRONOS_validation");
#if MINQ_VK_VALIDATION_LAYERS
		createInfo.enabledLayerCount = static_cast<uint32_t>(mqvk::g_VulkanContext.validationLayers.size());
		createInfo.ppEnabledLayerNames = mqvk::g_VulkanContext.validationLayers.data();

		debugCreateInfo = {};
		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugCreateInfo.pfnUserCallback = DebugCallback;
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
#else
		createInfo.enabledLayerCount = 0;

		createInfo.pNext = nullptr;
#endif

	CheckVkResult(vkCreateInstance(&createInfo, nullptr, &mqvk::g_VulkanContext.vkInstance));
}

void VulkanRenderSystem::CreateSurface()
{
	CheckVkResult(glfwCreateWindowSurface(mqvk::g_VulkanContext.vkInstance, mqvk::g_VulkanContext.glfwWindow, nullptr, &mqvk::g_VulkanContext.vkSurface));
}

void VulkanRenderSystem::SetupDebugMessenger()
{
#if MINQ_VK_VALIDATION_LAYERS
	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = DebugCallback;

	CheckVkResult(CreateDebugUtilsMessengerEXT(mqvk::g_VulkanContext.vkInstance, &createInfo, nullptr, &mqvk::g_VulkanContext.debugMessenger));
#endif
}

void VulkanRenderSystem::CreateVulkanDevice()
{
	mqvk::g_VulkanContext.vulkanDevice = MINQ_NEW(mqvk::VulkanDevice, kMemRenderSystem);
	mqvk::g_VulkanContext.vulkanDevice->InitVulkanDevice();
}

void VulkanRenderSystem::CreateSwapChain()
{
	mqvk::g_VulkanContext.SwapChain = MINQ_NEW(mqvk::VulkanSwapChain, kMemRenderSystem);
	mqvk::g_VulkanContext.SwapChain->CreateSwapChain();
}
