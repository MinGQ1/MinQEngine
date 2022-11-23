#pragma once
#include "Core/Layer.h"

class ImguiLayer : public Layer
{
public:
	bool Init();
	void Update() override;
private:
	bool CheckSupported();
};