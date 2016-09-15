#pragma once

#include <Windows.h>

namespace Test
{

	// Интерфес приложения
	class IApplication
	{

	protected:

		// Дескриптор приложения
		HINSTANCE hInstance = nullptr;

	public:

		IApplication(HINSTANCE hInstance = nullptr) : hInstance(hInstance){}

		virtual int Run(void) = 0;
		
	};
}