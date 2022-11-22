#pragma once

#include <cstddef>
#include "EventCommon.h"

namespace ArrowEngine {
	class EventMessage
	{
	public:
		EventMessage(int id): m_EventID(id)
		{
		}
		EventID GetEventID() const { return m_EventID; };
		void SetMessage(void* message) 
		{
			m_Message = message;
		}

		void* GetMessage() { return m_Message; }
	protected:
		const EventID m_EventID;
		void* m_Message;
	};
}