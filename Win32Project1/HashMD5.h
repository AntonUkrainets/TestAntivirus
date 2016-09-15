#pragma once

#include "IHash.h"
#include <memory>
#include "WrapHandle.h"
#include <string>
#include "WinApiException.h"

namespace Test
{

	// Класс вычисления MD5 хеша
	class HashMD5 : public IHash
	{

		// Алфавит, с которого состоит MD5
		const std::string	strDIGITS	= { "0123456789abcdef" };

		// Размер хеша в байтах при получении результата от WinCryptoApi
		const unsigned long	ulSIZE		= { 16 };

		// Обертки для хранения дескипторов WinCryptoApi
		using HWCP = HandleWinCryptoProvider;
		using HWCH = HandleWinCryptoHash;

		std::unique_ptr< HWCP > uptrProv, ptrHash;

	public:

		virtual ~HashMD5(void){ }

		// Метод, возвращающий в ввиде строки MD5 хеш полученных в параметрах данных
		std::string Hash(const std::vector< unsigned char > &vecData) override
		{

			this->uptrProv.reset(new HWCP);
			this->ptrHash.reset(new HWCH);

			if (!::CryptAcquireContext(*this->uptrProv,
				0,
				0,
				PROV_RSA_FULL,
				CRYPT_VERIFYCONTEXT))
				throw WinApiException("Ошибка создания криптографического контекста", ::GetLastError());

			if (!::CryptCreateHash(*this->uptrProv,
				CALG_MD5,
				0,
				0,
				*this->ptrHash))
				throw WinApiException("Ошибка создания хеша MD5", ::GetLastError());

			if (!::CryptHashData(*this->ptrHash,
				&vecData[0],
				vecData.size(),
				0))
				throw WinApiException("Ошибка вычисления хеша MD5", ::GetLastError());

			std::vector< BYTE > rgbHash(ulSIZE);
			unsigned long cbHash = ulSIZE;
			if (!::CryptGetHashParam(*this->ptrHash,
				HP_HASHVAL,
				&rgbHash[0],
				&cbHash,
				0))
				throw WinApiException("Ошибка получения хеша MD5", ::GetLastError());

			std::ostringstream stream;

			for (DWORD i = 0; i < cbHash; i++)
				stream << static_cast< char >(strDIGITS[rgbHash[i] >> 4]) << static_cast< char >(strDIGITS[rgbHash[i] & 0xf]);


			return stream.str();

		}


	};



}