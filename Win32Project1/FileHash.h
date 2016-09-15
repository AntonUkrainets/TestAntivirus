#pragma once

#include <fstream>
#include <vector>
#include <memory>
#include "IHash.h"


namespace Test
{

	// Класс вычисления хеша файла
	class FileHash
	{

		std::fstream &fstrFile;

		std::unique_ptr< IHash > uptrHash;

	public:

		FileHash(std::fstream &fstrFile,
			std::unique_ptr< IHash > uptrHash) : fstrFile(fstrFile), uptrHash(uptrHash.release()){}

		virtual				~FileHash(void){ }

		virtual std::string	Hash(void)
		{

			std::vector< unsigned char > vecBuf((std::istream_iterator<unsigned char>(this->fstrFile)), std::istream_iterator<unsigned char>());
			if (!vecBuf.size())
				throw std::exception();

			return this->uptrHash->Hash(vecBuf);

		}

	};

}