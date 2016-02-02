#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>

#include "command.h"
#include "layout.h"

class Command;

//����� ����������
class Processor
{
	friend class Command;
	friend class Arithmetic;
	friend class Compare;

	public:
		Processor();					//�����������.
		void start();					//������ ����� ��������� ������ ��.
		void setIP(Address _ip);
		~Processor();					//����������.

		//������ ��.
		Byte *Memory;

		//���.
		DataGPR *GPR;

	private:
		void loop();				//���� ������� ������ ��.

		//����� ������� �������.
		Address IP;

		//����� �������� �� ������������.
		Address callPoint;

		//������ ������ ��.
		Command *commands[Bit7];		

		//�����.
		struct Flags
		{
			unsigned char ZF : 1;
			unsigned char CF : 1;
			unsigned char OF : 1;
			unsigned char EF : 2;
		};

		Flags flags;
};

#endif