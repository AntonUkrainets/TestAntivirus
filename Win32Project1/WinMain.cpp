#include <Windows.h>
#include <tchar.h>
#include "App.h"

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment (lib, "comctl32.lib")


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{

	try
	{
		Test::App app(hInstance);
		return app.Run();
	}
	catch (const std::exception &ex)
	{
		MessageBox(0, ex.what(), 0, 0);
	}
	catch (...)
	{
		MessageBox(0, "Необработанное исключение", 0, 0);
	}
	return 0;
	
}

