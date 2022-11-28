#pragma once

#include "RenderSystems/RenderSystem.h"
#include "VulkanContext.h"

class VulkanRenderSystem : public RenderSystem
{
public:
	bool Initialize() override;

public:
	bool CreateInstance(const char* appName);
private:
	VulkanContext m_VulkanContext;
};