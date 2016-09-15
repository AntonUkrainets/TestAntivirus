#pragma once

namespace Test
{

	// Интерфейс сканирования объектов
	class IScaner
	{

	protected:

		// Флаг определения осуществляется проверка или нет
		bool bIsWorking = false;

	public:
		
		virtual ~IScaner(void){}

		virtual void Run(void) = 0;

		virtual void Stop(void) = 0;

		// Метод возвращающий статус работает или не работает проверка
		const bool & IsWorking(void)const throw()
		{
			return this->bIsWorking;
		}


	};
}