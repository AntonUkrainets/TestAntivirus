#pragma once
#include "IParamToThread.h"
#include "WrapHandle.h"
#include "WinApiException.h"
#include "CriticalSection.h"

namespace Test
{

	// Класс потока
	class Thread
	{

		// Критическая секция
		CriticalSection cs;

		// Параметры для потока
		IParamToThread *param;

		// Дескриптор потока
		std::unique_ptr< IHandle > uptrThread;

		Thread(const Thread&) = delete;
		const Thread & operator = (const Thread&) = delete;

		// Флаг определения, работает ли поток
		bool bIsWorking = false;

	public:

		Thread(IParamToThread *param = nullptr) : param(param), uptrThread(new HandleThread){}

		virtual ~Thread(void){}

		// Метод запуска потока
		void Run(void)
		{
			
			this->uptrThread.reset(new HandleThread(::CreateThread(0, 0, Task, this, 0, 0)));
			if (!*this->uptrThread)
				throw WinApiException("Ошибка запуска потока", ::GetLastError());

			this->SetStatus(true);

		}

		bool GetStatus(void)
		{
			bool bRet;
			this->cs.Enter();
			bRet = this->bIsWorking;
			this->cs.Leave();
			return bRet;

		}

		void SetStatus(const bool &bIsWorking)
		{

			this->cs.Enter();
			this->bIsWorking = bIsWorking;
			this->cs.Leave();

		}

		// Метод запуска потока
		void Run(IParamToThread *param)
		{

			this->param = param;
			this->Run();

		}

		// Ожидание завершение потока
		bool Wait(const unsigned long &ulWait = INFINITE) 
		{
		
			bool bReturn = this->GetStatus();
			if (!bReturn)
				return true;

			DWORD dwResult = ::WaitForSingleObject(*this->uptrThread, ulWait);
			
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

		// Закрытие дескриптора поткоа
		void Close(void)
		{
			this->uptrThread.reset(new HandleThread);
			this->SetStatus(false);
		}


	protected:

		// Функция выполняющаяся в отдельном потоке
		friend DWORD WINAPI Task(LPVOID p)
		{

			Thread *pTh = reinterpret_cast<Thread*>(p);

			pTh->param->DoWork();

			pTh->SetStatus(false);

			return 0;

		}

	};

}