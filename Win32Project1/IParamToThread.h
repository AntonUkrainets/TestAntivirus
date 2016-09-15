#pragma once
#include <string>

namespace Test
{
	
	// Интерфейс передачи параметров потоку
	class IParamToThread
	{

	public:

		virtual ~IParamToThread(void){}

		virtual void DoWork(void) throw() = 0;


	};

}