#include "processor.h"
#include "layout.h"

using namespace std;

//�����������.
Processor::Processor()
{
	Memory = new unsigned char[Bit16];
	GPR = new DataGPR[16];
	IP = 0;

	commands[2] = new Summation(*this);//2 - �������� ������� - �������(���������)
	commands[3] = new Summation(*this);		//3 - �������� ������� - �������(���������) (�����������)
	commands[4] = new Subtraction(*this);	//4 - ��������� ������� - �������(���������)
	commands[5] = new Subtraction(*this);	//5 - ��������� ������� - �������(���������) (�����������)
	commands[6] = new Multiplication(*this);//6 - ��������� ������� - �������(���������)
	commands[7] = new Multiplication(*this);//7 - ��������� ������� - �������(���������) (�����������)
	commands[8] = new Division(*this);		//8 - ������� ������� - �������(���������)
	commands[9] = new Division(*this);		//9 - ������� ������� - �������(���������) (�����������)
	commands[10] = new Compare(*this);		//10 - ��������� ������� - �������
	commands[11] = new Compare(*this);		//11 - ��������� ������� - �������(�����������)
	commands[12] = new Out(*this);			//12 - ����� ������� - (0, 1(CR LF))
	commands[13] = new Out(*this);			//13 - ����� ������� - (0, 1(CR LF)) (�����������)
	commands[14] = new Entry(*this);		//14 - ���� ������� - 0
	commands[15] = new Entry(*this);		//15 - ���� ������� - 0 (�����������)
	commands[16] = new Transference(*this);//16 - ���������� �������(��������) - �������(�������)


	commands[65] = new Summation(*this);	//65 - �������� ������� - 0(���������)-�����
	commands[66] = new Summation(*this);	//66 - �������� ������� - 0(���������)-�����(�����������)
	commands[67] = new Subtraction(*this);	//67 - ��������� ������� - 0(���������)-�����
	commands[68] = new Subtraction(*this);	//68 - ��������� ������� - 0(���������)-�����(�����������)
	commands[69] = new Multiplication(*this);//69 - ��������� ������� - 0(���������)-�����
	commands[70] = new Multiplication(*this);//70 - ��������� ������� - 0(���������)-�����(�����������)
	commands[71] = new Division(*this);		 //71 - ������� ������� - 0(���������)-�����
	commands[72] = new Division(*this);		//72 - ������� ������� - 0(���������)-�����(�����������)
	commands[73] = new Compare(*this);		//73 - ��������� ������� - 0 - �����
	commands[74] = new Compare(*this);		//74 - ��������� ������� - 0 - �����(�����������)
	commands[75] = new Out(*this);			//75 - ����� 0 - 0, 1(CR LF) - �����	
	commands[76] = new Out(*this);			//76 - ����� 0 - 0, 1(CR LF) - �����(�����������)
	commands[77] = new Entry(*this);		//77 - ���� 0 - 0 - �����
	commands[78] = new Entry(*this);		//78 - ���� 0 - 0 - �����(�����������)
	commands[79] = new Transference(*this);	//79 - ���������� 0 - �������(�������) - �����(��������)
	commands[80] = new Transference(*this);	//80 - ���������� 0 - �������(��������) - �����(�������)
	commands[81] = new Jump(*this);			//81 - ������� 0 - 0 - �����
}

//������ ����� ��������� ������ ��.
void Processor::start()
{
	loop();
}

void Processor::setIP(Address _ip)
{
	IP = _ip;
}

//���� ��������� ������ ��.
void Processor::loop()
{
	DataCommand32Bit data;

	data.d[0] = Memory[IP++];
	data.d[1] = Memory[IP++];

	while (data.cmd.type != 1)
	{
		if (data.cmd.type <= 64)
		{
			commands[data.cmd.type]->SetData(data.cmd);
			commands[data.cmd.type]->execute();
		}
		else
		{
			data.d[2] = Memory[IP++];
			data.d[3] = Memory[IP++];

			commands[data.cmd.type]->SetData(data.cmd);
			commands[data.cmd.type]->execute();
		}

		data.d[0] = Memory[IP++];
		data.d[1] = Memory[IP++];
	}
}

//����������.
Processor::~Processor()
{
	delete[] Memory;
	delete[] GPR;

	for (int i = 2; i < 16; i++)
	{
		delete commands[i];
		delete commands[i + 63];
	}

	delete commands[80];
}