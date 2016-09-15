#pragma once
#include <string>
#include "IControl.h"

namespace Test
{

	struct ParamToScan
	{

		// ���� � ������������ �����
		std::string strName;

		// ��������� �� ������ ����������� ���������
		IControl *pControl;

		// ��������� �� ������� ����������
		using PFN = void(*)(IControl *);
		PFN pFn;

	};

}