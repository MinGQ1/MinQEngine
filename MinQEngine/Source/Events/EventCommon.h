#pragma once

#define AE_EVENT_CALLBACK(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

typedef int EventID;

enum class EventIDCollector
{
// window EventID
	WindowClose = 0,
	WindowMove
};
