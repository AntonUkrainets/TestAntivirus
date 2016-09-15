#pragma once
#include "IEvent.h"

namespace Test
{

	// Интерфейс события
	class AutoEvent : public IEvent
	{

	public:

		AutoEvent(void) : IEvent(::CreateEvent(nullptr, 0, 0, nullptr)){ }

		virtual ~AutoEvent(void){}

		// Сброс события
		void Reset(void)const override
		{
			throw std::exception("Не поддерживается");
		}


	};

}