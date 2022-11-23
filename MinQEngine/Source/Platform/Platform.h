#pragma once
#include "MinQDefines.h"
#include "Core/Window.h"

ArrowEngine::Window* CreatePlatformWindow(const ArrowEngine::WndProps& prop);

double GetPlatformAbsoluteTime();
