#pragma once

#include "IControl.h"

namespace Test
{
	// Класс кнопка
	class TextBox : public IControl
	{

		TextBox(void) = delete;

	public:

		TextBox(HWND hWnd/*Дескриптор родительского окна*/,
			const int &idControl/*ID компонента*/)
			: IControl(hWnd, idControl) { }

		virtual ~TextBox(void){}

	};
}