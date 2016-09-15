#pragma once

#include <Windows.h>
#include <string>
#include "WinApiException.h"

namespace Test
{

	// Интерфейс для оконных контролов
	class IControl
	{

	protected:

		// Дескриптор контрола
		HWND hWnd = nullptr;

		// ID контрола
		int idControl = 0;

		IControl(void) = default;

	public:

		IControl(HWND hWnd/*Дескриптор родительского окна*/,
			const int &idControl/*ID компонента*/)
			: hWnd(hWnd),
			idControl(idControl) { }

		virtual ~IControl(void){}

		// Возврат текста контрола
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
					throw WinApiException("Ошибка получения текста с контрола", ::GetLastError());
				return strBuf.c_str();

			}

			return std::string();

		}

		// Установка текста контролу
		virtual void SetText(const std::string &strText) const
		{
			if (!::SetDlgItemText(this->hWnd,
				this->idControl,
				strText.c_str()))
				throw WinApiException("Ошибка присвоения текста контролу", ::GetLastError());

		}

		// Оператор преобразования
		operator HWND (void)const throw()
		{
			return this->hWnd;
		}

	};
}