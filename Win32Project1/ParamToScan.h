#pragma once
#include <string>
#include "IControl.h"

namespace Test
{

	struct ParamToScan
	{

		// Путь к проверяемому файлу
		std::string strName;

		// Указатель на объект отображения прогресса
		IControl *pControl;

		// Указатель на функцию завершения
		using PFN = void(*)(IControl *);
		PFN pFn;

	};

}