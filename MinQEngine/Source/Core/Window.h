#pragma once

#include <MinQDefines.h>
#include <Events/EventManager.h>

struct WndProps
{
	WndProps(UInt32 w, UInt32 h, const char* title): width(w), height(h), title(title)
	{
	}

	UInt32 width;
	UInt32 height;
	const char* title;
};

class Window
{
public:
	Window();
	virtual ~Window();

	virtual void* GetRealWindowPtr() = 0;
	virtual UInt32 GetWidth() = 0;
	virtual UInt32 GetHeight() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;
};
