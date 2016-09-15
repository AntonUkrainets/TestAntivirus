#pragma once
#include <string>
#include <Windows.h>
#include <sstream>


namespace Test
{

	// �����, �������������� ���������� �� ������ Windows API �������
	class WinApiException : public std::exception
	{

		unsigned long ulCode;
	
	public:
		
		WinApiException(const std::string &strMsg,	// ����� ��������� 
			const unsigned long &ulCode )			// ��� ������
			: std::exception(strMsg.c_str()), ulCode(ulCode){}

		virtual ~WinApiException(void){ }

		// ���������������� �����, ������������ ����������� ���������� �� ������
		const char * what(void) const override
		{

			static std::string strTmp;
			strTmp = std::string();

			LPVOID lpMsgBuf = NULL;

			::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				0,
				this->ulCode,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPSTR)&lpMsgBuf,
				0,
				0);

			std::ostringstream stream;

			stream << exception::what() << std::endl << "�����������: " << reinterpret_cast<LPCSTR>(lpMsgBuf) << "��� ������: " << this->ulCode;

			::LocalFree(lpMsgBuf);

			return strTmp.c_str();

		}

	};

}

