#pragma once
struct GLFWwindow;

class RenderSystem
{
public:
	virtual void Initialize();
	// TODO: remove this
	virtual void SetGlfwWindow(GLFWwindow* window);
	virtual void ShutDown();
};