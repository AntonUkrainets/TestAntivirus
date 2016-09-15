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

	// Класс проверки файла
	class FileScan : public IScaner, protected IParamToThread
	{

		// Структура параметров проверки
		ParamToScan paramToScan;

		// Объект для запуска задачи в отдельном потоке
		Thread th;

		// Объект события для прерывания проверки
		std::unique_ptr<IEvent> uptrEvent;

		std::ifstream ifsFileScan,	// Для чтения содержимого сканируемого файла
			ifsFileDbSig;			// Для чтения сигнатур с антивирусной базы

		// Фабрика создания объектов вычисления контрольных сумм
		FactoryHash factHash;
		
		// Имя файла базу сигнатур
		const std::string strDB = "main.mdb";

		// Размер файла базы данных сигнатур
		unsigned long ulSizeDbSize = 0;

		// Размер и MD5 проверяемого файла
		FileInfo fiCheck = FileInfo{};

	public:

		FileScan(const ParamToScan &paramToScan /*Параметры сканирования*/) 
			: paramToScan(paramToScan),
			uptrEvent(new AutoEvent) { }
		
		virtual ~FileScan(void){ }

		// Запуск сканирования
		void Run(void) override
		{

			// Открытие сканируемого файла
			this->OpenScanFile();

			// Открытие базы сигнатур
			this->OpenDbSigFile();

			// Вычисление и сохранение информации об сканируемом файле: Размер и MD5
			this->fiCheck = FileInfo::Get(this->ifsFileScan, this->factHash.Create());

			// Запуск проверки в отдельном потоке
			this->th.Run(this);

			// Установка флага работы
			IScaner::bIsWorking = true;
			
		}

		// Прерывание сканирования
		void Stop(void) override
		{
			
			// Установка события для завершения потока
			this->uptrEvent->Set();

			// Ожидание завершения потока
			while(!this->th.Wait(1000));

			// Сброс флага работы
			IScaner::bIsWorking = false;

			
		}

	protected:

		// Метод открытия сканируемого файла
		void OpenScanFile(void)
		{

			this->ifsFileScan.open(this->paramToScan.strName, std::ios::binary);
			if (!this->ifsFileScan.is_open())
				throw std::exception("Невозможно открыть сканируемый файл");

			this->ifsFileScan.unsetf(std::ios::skipws);

		}

		// Метод открытия файла базы данных сигнатур и возвращающий размер файла в байтах
		void OpenDbSigFile()
		{

			// Открытие базы сигнатур
			this->ifsFileDbSig.open(strDB, std::ios::ate);
			if (!this->ifsFileDbSig.is_open())
				throw std::exception("Невозможно открыть базу сигнатур");

			// Опеределение размера базы сигнатур
			this->ulSizeDbSize = static_cast< unsigned long >(this->ifsFileDbSig.tellg());

			this->ifsFileDbSig.seekg(0, std::ios::beg);

		}

		// Метод выполняющий работу
		void DoWork(void) override
		{
			
			try
			{

				// Количество сигнатур для вывода
				unsigned long ulCount = 0, ulOldPercent = 0, ulCurrPercent = 0;

				// Чтение сигнатур с базы
				while (!this->ifsFileDbSig.eof())
				{

					// Проверка на прерывание работы
					if (this->uptrEvent->Wait(1))
						return;
					
					FileInfo fiTmp;
					this->ifsFileDbSig >> fiTmp;

					// Сравнение по рамеру и MD5
					if (this->fiCheck == fiTmp)
					{

						// Закрытие файла
						this->ifsFileScan.close();

						std::ostringstream stream;
						stream << this->paramToScan.strName << " заражен" << std::endl;

						// Попытка удаления
						if (!::DeleteFile(this->paramToScan.strName.c_str()))
						{

							stream << "Ошибка удаления";
							throw WinApiException(stream.str(), ::GetLastError());
						
						}
						else
						{
						
							stream << "Удален успешно";
							throw std::exception(stream.str().c_str());
						
						}

					}

					ulCount += static_cast<unsigned long>(fiTmp);

					ulCurrPercent = (ulCount * 100) / this->ulSizeDbSize;

					if (ulOldPercent < ulCurrPercent || !ulOldPercent)
					{

						ulOldPercent = ulCurrPercent;
						
						// Количество проверенных сигнатур
						std::ostringstream stream;
						stream << "Проверено сигнатур " << ulOldPercent << "%";
						this->paramToScan.pControl->SetText(stream.str());

					}

				}

				throw std::exception("Файл чистый");

			}
			catch (const std::exception &ex)
			{

				MessageBox(0, ex.what(), 0, 0);

			}

			// Вызов функции завершения проверки
			this->paramToScan.pFn(this->paramToScan.pControl);

			// Сброс флага работы
			this->bIsWorking = false;

		}


	};
}