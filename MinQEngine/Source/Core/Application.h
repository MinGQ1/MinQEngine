#pragma once

#include <MinQDefines.h>
#include "Imgui/ImguiLayer.h"
#include "Window.h"
#include "LayerManager.h"

namespace ArrowEngine {

	class AE_API Application
	{
	public:
		Application();
		virtual ~Application();

		static Application* GetInstance() { return s_Instance; };
		Window* GetWindow() { return m_Window; };
		void Run();
	private:
		Window* m_Window;
		bool m_ShouldQuit;

		ImguiLayer* m_ImguiLayer;
		static Application* s_Instance;
	};

	Application* CreateApplication();
}


