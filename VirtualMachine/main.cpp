#include <iostream>
#include <string>

#include "processor.h"
#include "prototypes.h"

using namespace std;

int main()
{
	system("chcp 1251");
	system("cls");

	string file;

	cout << "Введите файл, для загрузки в память виртуальной машины.\n";
	cout << "->";
	cin >> file;

	Processor VM;
	Address ip;
	try
	{
		load(file, VM.Memory, ip);
		VM.setIP(ip);
		VM.start();
	}
	catch (int type)
	{
		if (type == -1)
			cout << "Файл не найден." << endl;
		if (type == -2)
			cout << "Не верный адрес." << endl;
		if (type == -3)
			cout << "Не верные данные." << endl;
	}

	cout << endl;
	system("pause");
}