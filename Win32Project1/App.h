#pragma once

#include "IApplication.h"
#include "resource.h"
#include "DialogFile.h"
#include "TestBox.h"
#include "Button.h"
#include "FileScan.h"

namespace Test
{

	// ID сообщения для функции завершения проверки
	enum { WM_FINISH = WM_USER + 1 };

	// Класс приложения
	class App : public IApplication, protected IControl
	{
		
		// Поле ввода пути к проверяемому файлу и кнопка
		std::unique_ptr< IControl > uptrTb, uptrBtn;

		// Объект для проверки файла
		std::unique_ptr< IScaner > uptrScanFile;
		
	public:

		App(HINSTANCE hInstance = nullptr) : IApplication(hInstance){}

		virtual ~App(void){}


		int Run(void)
		{

			// Загрузка диалога с ресурсов
			IControl::hWnd = ::CreateDialogParam(this->hInstance,
				MAKEINTRESOURCE(IDD_DIALOG1),
				0,
				WndProc,
				reinterpret_cast<LPARAM>(this));
			if (!IControl::hWnd)
				throw WinApiException("Ошибка создания окна приложения", ::GetLastError());
			
			// Отображение
			::ShowWindow(IControl::hWnd, SW_SHOW);

			// Создание объектов для управления полем ввода пути к файлу и кнопки сканирования
			this->uptrTb.reset(new Test::TextBox(IControl::hWnd, IDC_EDIT1));
			this->uptrBtn.reset(new Test::Button(IControl::hWnd, IDOK));

			MSG msg = { 0 };
			while (::GetMessage(&msg, NULL, NULL, NULL))
			{

				if (!::IsWindow(IControl::hWnd) || !::IsDialogMessage(IControl::hWnd, &msg))
				{

					::TranslateMessage(&msg);
					::DispatchMessage(&msg);

				}

			}

			return static_cast<int>(msg.wParam);

		}

	protected:

		// Функция обработки сообщений от системы и пользователя
		friend BOOL CALLBACK WndProc(HWND hWnd, 
			UINT uiMsg,
			WPARAM wParam, 
			LPARAM lParam)
		{
			
			static App *pApp = nullptr;

			switch (uiMsg)
			{

			// Инициализация окна приложения
			case WM_INITDIALOG:
				pApp = reinterpret_cast<App*>(lParam);
				return true;
				break;

				// Обработка выбора выбора пользователя
			case WM_COMMAND:
				switch (LOWORD(wParam))
				{

					// Выход с приложения
				case IDCANCEL:

					pApp->Exit();

					break;
					
					// Проверка файла или отмена проверки
				case IDOK:


					pApp->Scan();

				}
				break;

				// Завершение проверки
			case Test::WM_FINISH:
				while (pApp->uptrScanFile->IsWorking());
				//::Sleep(100);
				pApp->Stop();

				break;

				// Закрытие приложения
			case WM_CLOSE:
				::DestroyWindow(hWnd);
				::PostQuitMessage(0);
				break;

			}

			return false;
		}

		// Закрытие приложения
		void Exit(void) const
		{
			SendMessage(IControl::hWnd, WM_CLOSE, 0, 0);
		}

		// Метод запуска или остановки сканирования
		void Scan(void) 
		{

			// Если проверки файла нет
			if (!this->uptrScanFile.get())
				// Запуск сканирования
				this->Start();
			// Остановка
			else 
				this->Stop(true);

		}

		// Метод запуска проверки
		void Start(void)
		{
			try
			{

				try
				{

					// Если путь к файлу не указан
					if (this->uptrTb->GetText().empty())
						// Отображение диалога выбора файла
						this->uptrTb->SetText(Test::DialogFile(IControl::hWnd).File());

				}
				catch (std::exception)
				{
					// Пользователь отменил выбор файла
					return;
				}

				// Запуск проверки
				this->uptrScanFile.reset(new FileScan(ParamToScan{ this->uptrTb->GetText(), const_cast< App*>(this), FuncFinish }));
				this->uptrScanFile->Run();
				this->uptrBtn->SetText("Прервать");

			}
			catch (const std::exception &ex)
			{
				MessageBox(IControl::hWnd, ex.what(), 0, 0);
			}
		}

		// Метод прерывания или завершения сканирования
		void Stop(const bool &bStop = false)
		{
		
			try
			{

				// Прерывание сканирования
				this->uptrScanFile->Stop();
				this->uptrBtn->SetText("Сканировать");
				this->SetText("Test");
				this->uptrTb->SetText("");
				this->uptrScanFile.reset();

				if (bStop)
					MessageBox(0, "Прервано пользователем", 0, 0);


			}
			catch (const std::exception &ex)
			{
				MessageBox(IControl::hWnd, ex.what(), 0, 0);
			}
		}

		// Метод возвращающий текст заголовка окна приложения
		std::string GetText(void) const override
		{

			int iLen = ::SendMessage(IControl::hWnd, WM_GETTEXTLENGTH, 0, 0);
			if (iLen)
			{
				std::string strBuf(iLen + 1, '\0');
				::SendMessage(IControl::hWnd, WM_GETTEXT, strBuf.size(), reinterpret_cast<LPARAM>(&strBuf[0]));
				return strBuf.c_str();

			}

			return std::string();

		}

		// Метод вывода текста в загаловок окна приложения
		void SetText(const std::string &strText) const override
		{

			::SendMessage(IControl::hWnd, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(strText.c_str()));

		}

		// Функция завершения проверки
		friend void FuncFinish(IControl *pCnt)
		{

			::PostMessage(*pCnt, Test::WM_FINISH, 0, 0);

		}
		
	};
}