#pragma once
#include <Windows.h>

namespace Test
{
	class CriticalSection
	{
		CRITICAL_SECTION cs;
	public:
		CriticalSection(void)
		{
			::InitializeCriticalSection(&this->cs);
		}
		~CriticalSection(void)
		{
			::DeleteCriticalSection(&this->cs);
		}
		void Enter(void) 
		{
			::EnterCriticalSection(&this->cs);
		}

		void Leave(void) 
		{
			::LeaveCriticalSection(&this->cs);
		}
	};
}