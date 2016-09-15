#pragma once

#include "IApplication.h"
#include "resource.h"
#include "DialogFile.h"
#include "TestBox.h"
#include "Button.h"
#include "FileScan.h"

namespace Test
{

	// ID ��������� ��� ������� ���������� ��������
	enum { WM_FINISH = WM_USER + 1 };

	// ����� ����������
	class App : public IApplication, protected IControl
	{
		
		// ���� ����� ���� � ������������ ����� � ������
		std::unique_ptr< IControl > uptrTb, uptrBtn;

		// ������ ��� �������� �����
		std::unique_ptr< IScaner > uptrScanFile;
		
	public:

		App(HINSTANCE hInstance = nullptr) : IApplication(hInstance){}

		virtual ~App(void){}


		int Run(void)
		{

			// �������� ������� � ��������
			IControl::hWnd = ::CreateDialogParam(this->hInstance,
				MAKEINTRESOURCE(IDD_DIALOG1),
				0,
				WndProc,
				reinterpret_cast<LPARAM>(this));
			if (!IControl::hWnd)
				throw WinApiException("������ �������� ���� ����������", ::GetLastError());
			
			// �����������
			::ShowWindow(IControl::hWnd, SW_SHOW);

			// �������� �������� ��� ���������� ����� ����� ���� � ����� � ������ ������������
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

		// ������� ��������� ��������� �� ������� � ������������
		friend BOOL CALLBACK WndProc(HWND hWnd, 
			UINT uiMsg,
			WPARAM wParam, 
			LPARAM lParam)
		{
			
			static App *pApp = nullptr;

			switch (uiMsg)
			{

			// ������������� ���� ����������
			case WM_INITDIALOG:
				pApp = reinterpret_cast<App*>(lParam);
				return true;
				break;

				// ��������� ������ ������ ������������
			case WM_COMMAND:
				switch (LOWORD(wParam))
				{

					// ����� � ����������
				case IDCANCEL:

					pApp->Exit();

					break;
					
					// �������� ����� ��� ������ ��������
				case IDOK:


					pApp->Scan();

				}
				break;

				// ���������� ��������
			case Test::WM_FINISH:
				while (pApp->uptrScanFile->IsWorking());
				//::Sleep(100);
				pApp->Stop();

				break;

				// �������� ����������
			case WM_CLOSE:
				::DestroyWindow(hWnd);
				::PostQuitMessage(0);
				break;

			}

			return false;
		}

		// �������� ����������
		void Exit(void) const
		{
			SendMessage(IControl::hWnd, WM_CLOSE, 0, 0);
		}

		// ����� ������� ��� ��������� ������������
		void Scan(void) 
		{

			// ���� �������� ����� ���
			if (!this->uptrScanFile.get())
				// ������ ������������
				this->Start();
			// ���������
			else 
				this->Stop(true);

		}

		// ����� ������� ��������
		void Start(void)
		{
			try
			{

				try
				{

					// ���� ���� � ����� �� ������
					if (this->uptrTb->GetText().empty())
						// ����������� ������� ������ �����
						this->uptrTb->SetText(Test::DialogFile(IControl::hWnd).File());

				}
				catch (std::exception)
				{
					// ������������ ������� ����� �����
					return;
				}

				// ������ ��������
				this->uptrScanFile.reset(new FileScan(ParamToScan{ this->uptrTb->GetText(), const_cast< App*>(this), FuncFinish }));
				this->uptrScanFile->Run();
				this->uptrBtn->SetText("��������");

			}
			catch (const std::exception &ex)
			{
				MessageBox(IControl::hWnd, ex.what(), 0, 0);
			}
		}

		// ����� ���������� ��� ���������� ������������
		void Stop(const bool &bStop = false)
		{
		
			try
			{

				// ���������� ������������
				this->uptrScanFile->Stop();
				this->uptrBtn->SetText("�����������");
				this->SetText("Test");
				this->uptrTb->SetText("");
				this->uptrScanFile.reset();

				if (bStop)
					MessageBox(0, "�������� �������������", 0, 0);


			}
			catch (const std::exception &ex)
			{
				MessageBox(IControl::hWnd, ex.what(), 0, 0);
			}
		}

		// ����� ������������ ����� ��������� ���� ����������
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

		// ����� ������ ������ � ��������� ���� ����������
		void SetText(const std::string &strText) const override
		{

			::SendMessage(IControl::hWnd, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(strText.c_str()));

		}

		// ������� ���������� ��������
		friend void FuncFinish(IControl *pCnt)
		{

			::PostMessage(*pCnt, Test::WM_FINISH, 0, 0);

		}
		
	};
}