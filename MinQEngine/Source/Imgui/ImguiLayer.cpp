#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <imgui.h>
#include "ImguiLayer.h"
#include "ImguiGlfwBackend.h"
#include "ImguiVulkanBackend.h"
#include <glfw/glfw3.h>
#include "Core/Application.h"

bool ImguiLayer::CheckSupported()
{
	bool supported = true;
	supported &= glfwVulkanSupported() == GLFW_TRUE;
	return supported;
}

bool ImguiLayer::Init()
{
	if (!CheckSupported())
	{
		return false;
	}

	//ImGui_ImplGlfw_InitForVulkan();
}

void ImguiLayer::Update()
{
	ImGuiIO& io = ImGui::GetIO();
	Application* app = Application::GetInstance();
	io.DisplaySize = ImVec2(app->GetWindow()->GetWidth(), app->GetWindow()->GetHeight());

	ImGui_ImplVulkan_NewFrame();

}