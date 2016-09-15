#pragma once

#include "HashMD5.h"
#include <memory>


namespace Test
{

	// ������� �������� �������� ��� ���������� ����������� ���� ������
	class FactoryHash
	{

	public:

		virtual ~FactoryHash(void){}

		virtual std::unique_ptr<IHash> Create(void)
		{
			return std::unique_ptr<IHash>(new HashMD5);
		}

	};



}