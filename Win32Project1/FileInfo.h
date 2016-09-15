#pragma once
#include <string>
#include <memory>
#include "IHash.h"
#include <vector>
#include <fstream>
#include <regex>



namespace Test
{

	// ����� ���������� � �����
	class FileInfo
	{

		// ������, ��� � ���
		std::string strSize, strHash, strName;

		// ���������� ��������� ��� ������� ������ � ����: ������:���:��������� �� ��������� ������������
		static const std::regex REG;

		enum { SIZE = 1, HASH, NAME };

	public:
		
		FileInfo(void) = default;
		
		FileInfo(const std::string &strSize,			// ������ �����
			const std::string &strHash,					// ���
			const std::string &strName = std::string())	// ���
			: strSize(strSize), strHash(strHash), strName(strName){}

		virtual ~FileInfo(void){}

		
		// �������� ��������� ������� � ����
		bool operator ==(const FileInfo &fi) const throw()
		{

			if (this->strSize == fi.strSize)
				if (this->strHash == fi.strHash)
					return true;
			return false;

		}

		// ����� ������������ ���������� � ����������� �����
		static FileInfo Get(std::istream &fstrFile, // ���������� �����	���������� � �������� ���������� �������
			std::unique_ptr< IHash > uptrHash)		// ������ ���������� ���� �����
		{

			// ���������� ���������� �����
			std::vector< unsigned char > vecBuf((std::istream_iterator<unsigned char>(fstrFile)), std::istream_iterator<unsigned char>());
			if (!vecBuf.size())
				throw std::exception("����������� ���� ������");
			
			// �������
			return FileInfo(std::to_string(vecBuf.size())/*������ �����*/, uptrHash->Hash(vecBuf)/*���������� ����*/);
		
		}

		// ������������� �������� ������ ������ � �����
		friend std::ifstream & operator >> (std::ifstream &fs,	// ���������� ����� 
			FileInfo &fi)	// ������, � ������� ���������� ��������� ���������
		{
			
			// ���������� ������
			std::string strTmp;
			std::getline(fs, strTmp);
			
			// ��������� ������ ��: ������[1], ���[2] � ���������[3]
			std::smatch match;
			if (std::regex_search(strTmp, match, FileInfo::REG))
				// ���������� ����������
				fi = FileInfo(match[SIZE], match[HASH], match[NAME]);
			
			return fs;

		}

		operator unsigned long(void)const throw()
		{
			return this->strHash.size() + this->strName.size() + this->strSize.size();
		}

	};

	// ������������� ����������� ���������
	const std::regex FileInfo::REG("^(\\d{1,}):([0-9a-f]+):(.+)$");

}