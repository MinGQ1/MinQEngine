#pragma once
#include <ArrowEngine/Core/Layer.h>

namespace ArrowEngine
{
	class ImguiLayer : public Layer
	{
	public:
		bool Init();
		void Update() override;
	private:
		bool CheckSupported();
	};
}