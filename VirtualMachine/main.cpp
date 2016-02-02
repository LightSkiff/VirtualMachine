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

	cout << "������� ����, ��� �������� � ������ ����������� ������.\n";
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
			cout << "���� �� ������." << endl;
		if (type == -2)
			cout << "�� ������ �����." << endl;
		if (type == -3)
			cout << "�� ������ ������." << endl;
	}

	cout << endl;
	system("pause");
}