#pragma once

#include <Windows.h>
#include <string>
#include "WinApiException.h"

namespace Test
{

	// ��������� ��� ������� ���������
	class IControl
	{

	protected:

		// ���������� ��������
		HWND hWnd = nullptr;

		// ID ��������
		int idControl = 0;

		IControl(void) = default;

	public:

		IControl(HWND hWnd/*���������� ������������� ����*/,
			const int &idControl/*ID ����������*/)
			: hWnd(hWnd),
			idControl(idControl) { }

		virtual ~IControl(void){}

		// ������� ������ ��������
		virtual std::string GetText(void) const
		{

			int iLen = ::SendMessage(::GetDlgItem( this->hWnd, this->idControl), WM_GETTEXTLENGTH, 0, 0);
			if (iLen)
			{
				std::string strBuf(iLen + 1, '\0');
				if (!::GetDlgItemText(
					this->hWnd,
					this->idControl,
					&strBuf[0],
					static_cast<int>(strBuf.length())))
					throw WinApiException("������ ��������� ������ � ��������", ::GetLastError());
				return strBuf.c_str();

			}

			return std::string();

		}

		// ��������� ������ ��������
		virtual void SetText(const std::string &strText) const
		{
			if (!::SetDlgItemText(this->hWnd,
				this->idControl,
				strText.c_str()))
				throw WinApiException("������ ���������� ������ ��������", ::GetLastError());

		}

		// �������� ��������������
		operator HWND (void)const throw()
		{
			return this->hWnd;
		}

	};
}