#pragma once

#include "WrapHandle.h"
#include "WinApiException.h"

namespace Test
{

	// Интерфейс события
	class IEvent
	{

	protected:

		// Дескриптор события
		using HandleEvent = HandleThread;
		std::unique_ptr< IHandle > uptrEvent;

		IEvent(void) = delete;
		IEvent(const IEvent&) = delete;
		const IEvent & operator = (const IEvent&) = delete;

	public:

		IEvent(HANDLE h) : uptrEvent(new HandleEvent(h)){}

		virtual ~IEvent(void){}

		// Установка события
		void Set(void) const
		{

			if (!::SetEvent(*this->uptrEvent))
				throw WinApiException("Ошибка установи события", ::GetLastError());

		}

		// Ожидание события
		bool Wait(const unsigned long &ulWait = INFINITE) const
		{

			bool bReturn = false;

			DWORD dwResult = ::WaitForSingleObject(*this->uptrEvent, ulWait);

			switch (dwResult)
			{
			case WAIT_OBJECT_0:
				bReturn = true;
				break;
			case WAIT_FAILED:
				throw WinApiException("Ошибка ожидание завершения потока", ::GetLastError());

			}

			return bReturn;

		}

		// Оператор преобразования в дескриптор
		operator HANDLE(void)const throw()
		{
			return *this->uptrEvent;
		}

		// Закрытие дескриптора события
		void Close(void)
		{
			this->uptrEvent.reset(new HandleThread);
		}

		// Сброс события
		virtual void Reset(void)const = 0;


	};

}