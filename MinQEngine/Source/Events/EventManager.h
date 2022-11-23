#pragma once

#include <functional>
#include "EventMessage.h"

class EventListener
{
public:
	typedef std::function<void(const EventMessage&)> EventCallbackFn;
	virtual ~EventListener() = default;
	virtual void Handle(const EventMessage& message);
	virtual void SetCallback(const EventCallbackFn& callback);
private:
	EventCallbackFn m_EventCallback;
};

class  EventManager
{
public:
	virtual ~EventManager() = default;
	virtual void Subscribe(EventID eventID, EventListener* listener);
	virtual void Unsubscribe(EventID eventID, EventListener* listener);
	virtual void Notify(const EventMessage& msg);
private:
	std::unordered_map<EventID, std::list<EventListener*>*> m_ListenerMap;
};