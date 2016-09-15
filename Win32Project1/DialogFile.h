#pragma once
#include <string>
#include <Windows.h>

namespace Test
{
	// Класс отображения диалога
	class DialogFile
	{

		// Дескриптор родительского окна
		HWND hWnd;

	public:

		DialogFile(HWND hWnd = nullptr) : hWnd(hWnd){}

		virtual ~DialogFile(void){}

		// Метод возвращающий путь к выбраному файлу
		std::string File(void)const
		{
			
			OPENFILENAME ofn = { 0 };

			std::string strDir(MAX_PATH, '\0');
			std::string strFile(MAX_PATH, '\0');

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = &strDir[0];
			ofn.nMaxFile = strFile.size() - 1;
			ofn.lpstrFilter = nullptr;
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = &strFile[0];
			ofn.nMaxFileTitle = strFile.size() - 1;
			ofn.lpstrInitialDir = nullptr;
			ofn.Flags = OFN_EXPLORER;

			if (!::GetOpenFileName(&ofn))
				throw std::exception();

			return strDir.c_str();

		}

	};
}