#pragma once
#include "MinQDefines.h"
#include "Core/Window.h"

Window* CreatePlatformWindow(const WndProps& prop);

double GetPlatformAbsoluteTime();
