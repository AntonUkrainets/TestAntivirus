#pragma once

#include "IControl.h"

namespace Test
{
	// ����� ������
	class TextBox : public IControl
	{

		TextBox(void) = delete;

	public:

		TextBox(HWND hWnd/*���������� ������������� ����*/,
			const int &idControl/*ID ����������*/)
			: IControl(hWnd, idControl) { }

		virtual ~TextBox(void){}

	};
}