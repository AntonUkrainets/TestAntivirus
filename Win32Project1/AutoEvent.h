#pragma once
#include "IEvent.h"

namespace Test
{

	// ��������� �������
	class AutoEvent : public IEvent
	{

	public:

		AutoEvent(void) : IEvent(::CreateEvent(nullptr, 0, 0, nullptr)){ }

		virtual ~AutoEvent(void){}

		// ����� �������
		void Reset(void)const override
		{
			throw std::exception("�� ��������������");
		}


	};

}