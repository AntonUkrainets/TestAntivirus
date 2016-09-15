#pragma once

#include "WrapHandle.h"
#include "WinApiException.h"

namespace Test
{

	// ��������� �������
	class IEvent
	{

	protected:

		// ���������� �������
		using HandleEvent = HandleThread;
		std::unique_ptr< IHandle > uptrEvent;

		IEvent(void) = delete;
		IEvent(const IEvent&) = delete;
		const IEvent & operator = (const IEvent&) = delete;

	public:

		IEvent(HANDLE h) : uptrEvent(new HandleEvent(h)){}

		virtual ~IEvent(void){}

		// ��������� �������
		void Set(void) const
		{

			if (!::SetEvent(*this->uptrEvent))
				throw WinApiException("������ �������� �������", ::GetLastError());

		}

		// �������� �������
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
				throw WinApiException("������ �������� ���������� ������", ::GetLastError());

			}

			return bReturn;

		}

		// �������� �������������� � ����������
		operator HANDLE(void)const throw()
		{
			return *this->uptrEvent;
		}

		// �������� ����������� �������
		void Close(void)
		{
			this->uptrEvent.reset(new HandleThread);
		}

		// ����� �������
		virtual void Reset(void)const = 0;


	};

}