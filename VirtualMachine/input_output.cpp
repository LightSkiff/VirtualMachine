#include <iostream>

#include "command.h"

Out::Out(Processor &_curProc)
	: Command(_curProc)
{
}

void Out::execute()
{
	if (data.type == 12)	outR();
	else if (data.type == 75) outA();
	else if (data.type == 13) outUR();
	else if (data.type == 76) outUA();
}

void Out::outR()
{
	if (data.s == 0)
	{
		std::cout << curProc->GPR[data.r1].Memory_i;
		std::cout << " ";

		if (data.r2 == 1)
			std::cout << std::endl;
	}
	else
	{
		DataFloat tmp;

		tmp.d[0] = curProc->GPR[data.r1].d[0];
		tmp.d[1] = curProc->GPR[data.r1].d[1];
		tmp.d[2] = curProc->GPR[data.r1 + 1].d[0];
		tmp.d[3] = curProc->GPR[data.r1 + 1].d[1];

		std::cout << tmp.Memory_f;
		std::cout << " ";

		if (data.r2 == 1)
			std::cout << std::endl;
	}
}

void Out::outA()
{
	if (data.s == 0)
	{
		DataInt tmp;

		tmp.d[0] = curProc->Memory[data.off];
		tmp.d[1] = curProc->Memory[data.off + 1];

		std::cout << tmp.Memory_i;
		std::cout << " ";

		if (data.r2 == 1)
			std::cout << std::endl;
	}
	else
	{
		DataFloat tmp;

		tmp.d[0] = curProc->Memory[data.off];
		tmp.d[1] = curProc->Memory[data.off + 1];
		tmp.d[2] = curProc->Memory[data.off + 2];
		tmp.d[3] = curProc->Memory[data.off + 3];

		std::cout << tmp.Memory_f;
		std::cout << " ";

		if (data.r2 == 1)
			std::cout << std::endl;
	}
}

void Out::outUR()
{
	std::cout << curProc->GPR[data.r1].Memory_u;
	std::cout << " ";

	if (data.r2 == 1)
		std::cout << std::endl;
}

void Out::outUA()
{
	DataUint tmp;

	tmp.d[0] = curProc->Memory[data.off];
	tmp.d[1] = curProc->Memory[data.off + 1];

	std::cout << tmp.Memory_u;
	std::cout << " ";

	if (data.r2 == 1)
		std::cout << std::endl;
}

Entry::Entry(Processor &_curProc)
	: Command(_curProc)
{
}

void Entry::execute()
{
	if (data.type == 14)	entryR();
	else if (data.type == 77) entryA();
	else if (data.type == 15) entryUR();
	else if (data.type == 78) entryUA();
}

void Entry::entryR()
{
	if (data.s == 0)
	{
		DataInt tmp;
		std::cout << std::endl << "(integer)->";
		std::cin >> tmp.Memory_i;

		curProc->GPR[data.r1].d[0] = tmp.d[0];
		curProc->GPR[data.r1].d[1] = tmp.d[1];
	}
	else
	{
		DataFloat tmp;
		std::cout << std::endl << "(float)->";
		std::cin >> tmp.Memory_f;

		curProc->GPR[data.r1].d[0] = tmp.d[0];
		curProc->GPR[data.r1].d[1] = tmp.d[1];
		curProc->GPR[data.r1 + 1].d[0] = tmp.d[2];
		curProc->GPR[data.r1 + 1].d[1] = tmp.d[3];
	}
}

void Entry::entryA()
{
	if (data.s == 0)
	{
		DataInt tmp;
		std::cout << std::endl << "(integer)->";
		std::cin >> tmp.Memory_i;

		curProc->Memory[data.off] = tmp.d[0];
		curProc->Memory[data.off + 1] = tmp.d[1];
	}
	else
	{
		DataFloat tmp;
		std::cout << std::endl << "(float)->";
		std::cin >> tmp.Memory_f;

		curProc->Memory[data.off] = tmp.d[0];
		curProc->Memory[data.off + 1] = tmp.d[1];
		curProc->Memory[data.off + 2] = tmp.d[2];
		curProc->Memory[data.off + 3] = tmp.d[3];
	}
}

void Entry::entryUR()
{
	DataUint tmp;
	std::cout << std::endl << "(unsigned)->";
	std::cin >> tmp.Memory_u;

	curProc->GPR[data.r1].d[0] = tmp.d[0];
	curProc->GPR[data.r1].d[1] = tmp.d[1];
}

void Entry::entryUA()
{
	DataUint tmp;
	std::cout << std::endl << "(unsigned)->";
	std::cin >> tmp.Memory_u;

	curProc->Memory[data.off] = tmp.d[0];
	curProc->Memory[data.off + 1] = tmp.d[1];
}