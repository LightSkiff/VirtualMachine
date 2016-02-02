#include "processor.h"
#include "layout.h"

using namespace std;

//Конструктор.
Processor::Processor()
{
	Memory = new unsigned char[Bit16];
	GPR = new DataGPR[16];
	IP = 0;

	commands[2] = new Summation(*this);//2 - сложение регистр - регистр(результат)
	commands[3] = new Summation(*this);		//3 - сложение регистр - регистр(результат) (беззнаковое)
	commands[4] = new Subtraction(*this);	//4 - вычитание регистр - регистр(результат)
	commands[5] = new Subtraction(*this);	//5 - вычитание регистр - регистр(результат) (беззнаковое)
	commands[6] = new Multiplication(*this);//6 - умножение регистр - регистр(результат)
	commands[7] = new Multiplication(*this);//7 - умножение регистр - регистр(результат) (беззнаковое)
	commands[8] = new Division(*this);		//8 - деление регистр - регистр(результат)
	commands[9] = new Division(*this);		//9 - деление регистр - регистр(результат) (беззнаковое)
	commands[10] = new Compare(*this);		//10 - сравнение регистр - регистр
	commands[11] = new Compare(*this);		//11 - сравнение регистр - регистр(беззнаковое)
	commands[12] = new Out(*this);			//12 - вывод регистр - (0, 1(CR LF))
	commands[13] = new Out(*this);			//13 - вывод регистр - (0, 1(CR LF)) (беззнаковое)
	commands[14] = new Entry(*this);		//14 - ввод регистр - 0
	commands[15] = new Entry(*this);		//15 - ввод регистр - 0 (беззнаковое)
	commands[16] = new Transference(*this);//16 - перессылка регистр(источник) - регистр(приёмник)


	commands[65] = new Summation(*this);	//65 - сложение регистр - 0(результат)-адрес
	commands[66] = new Summation(*this);	//66 - сложение регистр - 0(результат)-адрес(беззнаковое)
	commands[67] = new Subtraction(*this);	//67 - вычитание регистр - 0(результат)-адрес
	commands[68] = new Subtraction(*this);	//68 - вычитание регистр - 0(результат)-адрес(беззнаковое)
	commands[69] = new Multiplication(*this);//69 - умножение регистр - 0(результат)-адрес
	commands[70] = new Multiplication(*this);//70 - умножение регистр - 0(результат)-адрес(беззнаковое)
	commands[71] = new Division(*this);		 //71 - деление регистр - 0(результат)-адрес
	commands[72] = new Division(*this);		//72 - деление регистр - 0(результат)-адрес(беззнаковое)
	commands[73] = new Compare(*this);		//73 - сравнение регистр - 0 - адрес
	commands[74] = new Compare(*this);		//74 - сравнение регистр - 0 - адрес(беззнаковое)
	commands[75] = new Out(*this);			//75 - вывод 0 - 0, 1(CR LF) - адрес	
	commands[76] = new Out(*this);			//76 - вывод 0 - 0, 1(CR LF) - адрес(беззнаковое)
	commands[77] = new Entry(*this);		//77 - ввод 0 - 0 - адрес
	commands[78] = new Entry(*this);		//78 - ввод 0 - 0 - адрес(беззнаковое)
	commands[79] = new Transference(*this);	//79 - перессылка 0 - регистр(приёмник) - адрес(источник)
	commands[80] = new Transference(*this);	//80 - перессылка 0 - регистр(источник) - адрес(приёмник)
	commands[81] = new Jump(*this);			//81 - переход 0 - 0 - адрес
}

//Запуск цикла обработки команд ВМ.
void Processor::start()
{
	loop();
}

void Processor::setIP(Address _ip)
{
	IP = _ip;
}

//Цикл обработки команд ВМ.
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

//Деструктор.
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