#pragma once

#include "HashMD5.h"
#include <memory>


namespace Test
{

	// Фабрика создания объектов для вычисления контрольных сумм данных
	class FactoryHash
	{

	public:

		virtual ~FactoryHash(void){}

		virtual std::unique_ptr<IHash> Create(void)
		{
			return std::unique_ptr<IHash>(new HashMD5);
		}

	};



}