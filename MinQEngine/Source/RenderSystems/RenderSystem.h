#pragma once
struct GLFWwindow;

class RenderSystem
{
public:
	virtual void Initialize();
	virtual void ShutDown();
};