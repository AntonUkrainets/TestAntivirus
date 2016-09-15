#pragma once

#include <string>
#include <vector>

namespace Test
{
	// Интерфейс для вычисления контрольных сумм данных
	class IHash
	{

	public:

		virtual				~IHash(void){ }

		virtual std::string Hash(const std::vector< unsigned char > &) = 0;

	};

}