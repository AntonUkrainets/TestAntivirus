#pragma once
#include <string>
#include <memory>
#include "IHash.h"
#include <vector>
#include <fstream>
#include <regex>



namespace Test
{

	// Класс информации о файле
	class FileInfo
	{

		// Размер, хеш и имя
		std::string strSize, strHash, strName;

		// Регулярное выражение для разбора строки с вида: Размер:Хеш:ИмяВируса на отдельные составляющие
		static const std::regex REG;

		enum { SIZE = 1, HASH, NAME };

	public:
		
		FileInfo(void) = default;
		
		FileInfo(const std::string &strSize,			// Размер файла
			const std::string &strHash,					// Хеш
			const std::string &strName = std::string())	// Имя
			: strSize(strSize), strHash(strHash), strName(strName){}

		virtual ~FileInfo(void){}

		
		// Оператор сравнения размера и хеша
		bool operator ==(const FileInfo &fi) const throw()
		{

			if (this->strSize == fi.strSize)
				if (this->strHash == fi.strHash)
					return true;
			return false;

		}

		// Метод возвращающий информацию о сканируемом файле
		static FileInfo Get(std::istream &fstrFile, // Дескриптор файла	информацию с которого необходимо вернуть
			std::unique_ptr< IHash > uptrHash)		// Объект вычисления хеша файла
		{

			// Считывание содержимое файла
			std::vector< unsigned char > vecBuf((std::istream_iterator<unsigned char>(fstrFile)), std::istream_iterator<unsigned char>());
			if (!vecBuf.size())
				throw std::exception("Сканируемый файл пустой");
			
			// Возврат
			return FileInfo(std::to_string(vecBuf.size())/*Размер файла*/, uptrHash->Hash(vecBuf)/*Вычисление хеша*/);
		
		}

		// Перегруженный оператор чтения данных с файла
		friend std::ifstream & operator >> (std::ifstream &fs,	// Дескриптор файла 
			FileInfo &fi)	// Объект, в которые необходимо сохранить результат
		{
			
			// Считывание строки
			std::string strTmp;
			std::getline(fs, strTmp);
			
			// Разбиение строки на: Размер[1], Хеш[2] и ИмяВируса[3]
			std::smatch match;
			if (std::regex_search(strTmp, match, FileInfo::REG))
				// Сохранение результата
				fi = FileInfo(match[SIZE], match[HASH], match[NAME]);
			
			return fs;

		}

		operator unsigned long(void)const throw()
		{
			return this->strHash.size() + this->strName.size() + this->strSize.size();
		}

	};

	// Инициализация регулярного выражения
	const std::regex FileInfo::REG("^(\\d{1,}):([0-9a-f]+):(.+)$");

}