#pragma once
#include <string>

namespace Test
{
	
	// ��������� �������� ���������� ������
	class IParamToThread
	{

	public:

		virtual ~IParamToThread(void){}

		virtual void DoWork(void) throw() = 0;


	};

}