#pragma once

#include "IHash.h"
#include <memory>
#include "WrapHandle.h"
#include <string>
#include "WinApiException.h"

namespace Test
{

	// ����� ���������� MD5 ����
	class HashMD5 : public IHash
	{

		// �������, � �������� ������� MD5
		const std::string	strDIGITS	= { "0123456789abcdef" };

		// ������ ���� � ������ ��� ��������� ���������� �� WinCryptoApi
		const unsigned long	ulSIZE		= { 16 };

		// ������� ��� �������� ����������� WinCryptoApi
		using HWCP = HandleWinCryptoProvider;
		using HWCH = HandleWinCryptoHash;

		std::unique_ptr< HWCP > uptrProv, ptrHash;

	public:

		virtual ~HashMD5(void){ }

		// �����, ������������ � ����� ������ MD5 ��� ���������� � ���������� ������
		std::string Hash(const std::vector< unsigned char > &vecData) override
		{

			this->uptrProv.reset(new HWCP);
			this->ptrHash.reset(new HWCH);

			if (!::CryptAcquireContext(*this->uptrProv,
				0,
				0,
				PROV_RSA_FULL,
				CRYPT_VERIFYCONTEXT))
				throw WinApiException("������ �������� ������������������ ���������", ::GetLastError());

			if (!::CryptCreateHash(*this->uptrProv,
				CALG_MD5,
				0,
				0,
				*this->ptrHash))
				throw WinApiException("������ �������� ���� MD5", ::GetLastError());

			if (!::CryptHashData(*this->ptrHash,
				&vecData[0],
				vecData.size(),
				0))
				throw WinApiException("������ ���������� ���� MD5", ::GetLastError());

			std::vector< BYTE > rgbHash(ulSIZE);
			unsigned long cbHash = ulSIZE;
			if (!::CryptGetHashParam(*this->ptrHash,
				HP_HASHVAL,
				&rgbHash[0],
				&cbHash,
				0))
				throw WinApiException("������ ��������� ���� MD5", ::GetLastError());

			std::ostringstream stream;

			for (DWORD i = 0; i < cbHash; i++)
				stream << static_cast< char >(strDIGITS[rgbHash[i] >> 4]) << static_cast< char >(strDIGITS[rgbHash[i] & 0xf]);


			return stream.str();

		}


	};



}