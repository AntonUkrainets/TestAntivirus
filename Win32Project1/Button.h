#pragma once

#include "IControl.h"

namespace Test
{
	// ����� ������
	class Button : public IControl
	{

		Button(void) = delete;

	public:

		Button(HWND hWnd/*���������� ������������� ����*/,
			const int &idControl/*ID ����������*/)
			: IControl(hWnd, idControl) { }

		virtual ~Button(void){}

	};
}