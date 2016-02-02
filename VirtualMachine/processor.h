#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>

#include "command.h"
#include "layout.h"

class Command;

//Класс процессора
class Processor
{
	friend class Command;
	friend class Arithmetic;
	friend class Compare;

	public:
		Processor();					//Конструктор.
		void start();					//Запуск цикла обработки команд ВМ.
		void setIP(Address _ip);
		~Processor();					//Деструктор.

		//Память ВМ.
		Byte *Memory;

		//Рон.
		DataGPR *GPR;

	private:
		void loop();				//Цикл обратки команд ВМ.

		//Адрес текущей команды.
		Address IP;

		//Точка возврата из подпрограммы.
		Address callPoint;

		//Массив команд ВМ.
		Command *commands[Bit7];		

		//Флаги.
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