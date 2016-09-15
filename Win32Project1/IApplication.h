#pragma once

#include <Windows.h>

namespace Test
{

	// �������� ����������
	class IApplication
	{

	protected:

		// ���������� ����������
		HINSTANCE hInstance = nullptr;

	public:

		IApplication(HINSTANCE hInstance = nullptr) : hInstance(hInstance){}

		virtual int Run(void) = 0;
		
	};
}