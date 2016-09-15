#pragma once

#include "IControl.h"

namespace Test
{
	// Класс кнопка
	class Button : public IControl
	{

		Button(void) = delete;

	public:

		Button(HWND hWnd/*Дескриптор родительского окна*/,
			const int &idControl/*ID компонента*/)
			: IControl(hWnd, idControl) { }

		virtual ~Button(void){}

	};
}