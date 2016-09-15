#pragma once

namespace Test
{

	// ��������� ������������ ��������
	class IScaner
	{

	protected:

		// ���� ����������� �������������� �������� ��� ���
		bool bIsWorking = false;

	public:
		
		virtual ~IScaner(void){}

		virtual void Run(void) = 0;

		virtual void Stop(void) = 0;

		// ����� ������������ ������ �������� ��� �� �������� ��������
		const bool & IsWorking(void)const throw()
		{
			return this->bIsWorking;
		}


	};
}