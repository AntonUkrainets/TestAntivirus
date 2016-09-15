#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "FileHash.h"
#include "HashMD5.h"
#include "FileInfo.h"
#include "FactoryHash.h"
#include "IScaner.h"
#include "ParamToScan.h"
#include "IParamToThread.h"
#include "Thread.h"
#include "AutoEvent.h"

namespace Test
{

	// ����� �������� �����
	class FileScan : public IScaner, protected IParamToThread
	{

		// ��������� ���������� ��������
		ParamToScan paramToScan;

		// ������ ��� ������� ������ � ��������� ������
		Thread th;

		// ������ ������� ��� ���������� ��������
		std::unique_ptr<IEvent> uptrEvent;

		std::ifstream ifsFileScan,	// ��� ������ ����������� ������������ �����
			ifsFileDbSig;			// ��� ������ �������� � ������������ ����

		// ������� �������� �������� ���������� ����������� ����
		FactoryHash factHash;
		
		// ��� ����� ���� ��������
		const std::string strDB = "main.mdb";

		// ������ ����� ���� ������ ��������
		unsigned long ulSizeDbSize = 0;

		// ������ � MD5 ������������ �����
		FileInfo fiCheck = FileInfo{};

	public:

		FileScan(const ParamToScan &paramToScan /*��������� ������������*/) 
			: paramToScan(paramToScan),
			uptrEvent(new AutoEvent) { }
		
		virtual ~FileScan(void){ }

		// ������ ������������
		void Run(void) override
		{

			// �������� ������������ �����
			this->OpenScanFile();

			// �������� ���� ��������
			this->OpenDbSigFile();

			// ���������� � ���������� ���������� �� ����������� �����: ������ � MD5
			this->fiCheck = FileInfo::Get(this->ifsFileScan, this->factHash.Create());

			// ������ �������� � ��������� ������
			this->th.Run(this);

			// ��������� ����� ������
			IScaner::bIsWorking = true;
			
		}

		// ���������� ������������
		void Stop(void) override
		{
			
			// ��������� ������� ��� ���������� ������
			this->uptrEvent->Set();

			// �������� ���������� ������
			while(!this->th.Wait(1000));

			// ����� ����� ������
			IScaner::bIsWorking = false;

			
		}

	protected:

		// ����� �������� ������������ �����
		void OpenScanFile(void)
		{

			this->ifsFileScan.open(this->paramToScan.strName, std::ios::binary);
			if (!this->ifsFileScan.is_open())
				throw std::exception("���������� ������� ����������� ����");

			this->ifsFileScan.unsetf(std::ios::skipws);

		}

		// ����� �������� ����� ���� ������ �������� � ������������ ������ ����� � ������
		void OpenDbSigFile()
		{

			// �������� ���� ��������
			this->ifsFileDbSig.open(strDB, std::ios::ate);
			if (!this->ifsFileDbSig.is_open())
				throw std::exception("���������� ������� ���� ��������");

			// ������������ ������� ���� ��������
			this->ulSizeDbSize = static_cast< unsigned long >(this->ifsFileDbSig.tellg());

			this->ifsFileDbSig.seekg(0, std::ios::beg);

		}

		// ����� ����������� ������
		void DoWork(void) override
		{
			
			try
			{

				// ���������� �������� ��� ������
				unsigned long ulCount = 0, ulOldPercent = 0, ulCurrPercent = 0;

				// ������ �������� � ����
				while (!this->ifsFileDbSig.eof())
				{

					// �������� �� ���������� ������
					if (this->uptrEvent->Wait(1))
						return;
					
					FileInfo fiTmp;
					this->ifsFileDbSig >> fiTmp;

					// ��������� �� ������ � MD5
					if (this->fiCheck == fiTmp)
					{

						// �������� �����
						this->ifsFileScan.close();

						std::ostringstream stream;
						stream << this->paramToScan.strName << " �������" << std::endl;

						// ������� ��������
						if (!::DeleteFile(this->paramToScan.strName.c_str()))
						{

							stream << "������ ��������";
							throw WinApiException(stream.str(), ::GetLastError());
						
						}
						else
						{
						
							stream << "������ �������";
							throw std::exception(stream.str().c_str());
						
						}

					}

					ulCount += static_cast<unsigned long>(fiTmp);

					ulCurrPercent = (ulCount * 100) / this->ulSizeDbSize;

					if (ulOldPercent < ulCurrPercent || !ulOldPercent)
					{

						ulOldPercent = ulCurrPercent;
						
						// ���������� ����������� ��������
						std::ostringstream stream;
						stream << "��������� �������� " << ulOldPercent << "%";
						this->paramToScan.pControl->SetText(stream.str());

					}

				}

				throw std::exception("���� ������");

			}
			catch (const std::exception &ex)
			{

				MessageBox(0, ex.what(), 0, 0);

			}

			// ����� ������� ���������� ��������
			this->paramToScan.pFn(this->paramToScan.pControl);

			// ����� ����� ������
			this->bIsWorking = false;

		}


	};
}