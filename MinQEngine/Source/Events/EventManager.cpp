#include <Logger/Log.h>
#include <Logger/Assert.h>
#include "EventManager.h"

void EventListener::SetCallback(const EventCallbackFn& callback) 
{
	m_EventCallback = callback;
}

void EventListener::Handle(const EventMessage& message)
{
	LogWarn(m_EventCallback != NULL);
	m_EventCallback(message);
}

void  EventManager::Subscribe(EventID eventID, EventListener* listener)
{
	if (m_ListenerMap.find(eventID) == m_ListenerMap.end())
	{
		m_ListenerMap.insert(std::pair<EventID, std::list<EventListener*>*>(eventID, new std::list<EventListener*>()));
	}
	if (!m_ListenerMap[eventID])
	{
		LogWarn("EventManager: Subscrbe Failed");
		return;
	}

	std::list<EventListener*>* list = m_ListenerMap[eventID];
	for (std::list<EventListener*>::iterator it = list->begin(); it != list->end(); ++it)
	{
		if ((*it) == listener)
		{
			LogWarn("EventManager: Already Subscrbed Listener");
			return;
		}
	}

	m_ListenerMap[eventID]->push_back(listener);
}

void EventManager::Unsubscribe(EventID eventID, EventListener* listener)
{
	if (m_ListenerMap.find(eventID) == m_ListenerMap.end())
	{
		LogWarn("EventManager: Unsubscribe Failed");
		return;
	}
	std::list<EventListener*>* list = m_ListenerMap[eventID];
	for (std::list<EventListener*>::iterator it = list->begin(); it != list->end(); ++it)
	{
		if ((*it) == listener) 
		{
			list->erase(it);
		}
	}
}

void EventManager::Notify(const EventMessage& msg)
{
	EventID eventID = msg.GetEventID();
	auto it = m_ListenerMap.find(eventID);
	if (it == m_ListenerMap.end())
	{
		LogWarn("EventManager: Notify Failed With ID: " + eventID);
		return;
	}
	std::list<EventListener*>* list = m_ListenerMap[eventID];
	for (std::list<EventListener*>::iterator it = list->begin(); it != list->end(); ++it)
	{
		(*it)->Handle(msg);
	}
}