#include "command.h"

Command::Command(Processor &_curProc)
	: curProc(&_curProc)
{
}

void Command::SetData(const Command32Bit &obj)
{
	data = obj;
}

void Command::operator()()
{
	execute();
}

Command::~Command()
{
}

Compare::Compare(Processor &_curProc)
	: Command(_curProc)
{
}

void Compare::execute()
{
	if (data.type == 10) R();
	else if (data.type == 73) A();
	else if (data.type == 11)  UR();
	else if (data.type == 74) UA();
}

void Compare::R()
{
	if (data.s == 0)
	{
		DataInt op1;
		DataInt op2;

		op1.Memory_i = curProc->GPR[data.r1].Memory_i;
		op2.Memory_i = curProc->GPR[data.r2].Memory_i;

		if (op1.Memory_i > op2.Memory_i)		
			curProc->flags.OF = 1;
		else if (op1.Memory_i < op2.Memory_i)	
			curProc->flags.OF = -1;
		else	
			curProc->flags.OF = 0;
	}
	else
	{
		DataFloat op1;
		DataFloat op2;

		op1.d[0] = curProc->GPR[data.r1].d[0];
		op1.d[1] = curProc->GPR[data.r1].d[1];
		op1.d[2] = curProc->GPR[data.r1 + 1].d[0];
		op1.d[3] = curProc->GPR[data.r1 + 1].d[1];
		op2.d[0] = curProc->GPR[data.r2].d[0];
		op2.d[1] = curProc->GPR[data.r2].d[1];
		op2.d[2] = curProc->GPR[data.r2 + 1].d[0];
		op2.d[3] = curProc->GPR[data.r2 + 1].d[1];

		if (op1.Memory_f > op2.Memory_f)
			curProc->flags.OF = 1;
		else if (op1.Memory_f < op2.Memory_f)
			curProc->flags.OF = -1;
		else
			curProc->flags.OF = 0;
	}
}

void Compare::A()
{
	if (data.s == 0)
	{
		DataInt op1;
		DataInt op2;

		op1.Memory_i = curProc->GPR[data.r1].Memory_i;
		op2.d[0] = curProc->Memory[data.off];
		op2.d[1] = curProc->Memory[data.off + 1];

		if (op1.Memory_i > op2.Memory_i)
			curProc->flags.OF = 1;
		else if (op1.Memory_i < op2.Memory_i)
			curProc->flags.OF = -1;
		else
			curProc->flags.OF = 0;
	}
	else
	{
		DataFloat op1;
		DataFloat op2;

		op1.d[0] = curProc->GPR[data.r1].d[0];
		op1.d[1] = curProc->GPR[data.r1].d[1];
		op1.d[2] = curProc->GPR[data.r1 + 1].d[0];
		op1.d[3] = curProc->GPR[data.r1 + 1].d[1];
		op2.d[0] = curProc->Memory[data.off];
		op2.d[1] = curProc->Memory[data.off + 1];
		op2.d[2] = curProc->Memory[data.off + 2];
		op2.d[3] = curProc->Memory[data.off + 3];

		if (op1.Memory_f > op2.Memory_f)
			curProc->flags.OF = 1;
		else if (op1.Memory_f < op2.Memory_f)
			curProc->flags.OF = -1;
		else
			curProc->flags.OF = 0;
	}
}

void Compare::UR()
{
	DataUint op1;
	DataUint op2;

	op1.Memory_u = curProc->GPR[data.r1].Memory_i;
	op2.Memory_u = curProc->GPR[data.r2].Memory_i;

	if (op1.Memory_u > op2.Memory_u)
		curProc->flags.OF = 1;
	else if (op1.Memory_u < op2.Memory_u)
		curProc->flags.OF = -1;
	else
		curProc->flags.OF = 0;
}

void Compare::UA()
{
	DataUint op1;
	DataUint op2;

	op1.Memory_u = curProc->GPR[data.r1].Memory_i;
	op2.d[0] = curProc->Memory[data.off];
	op2.d[1] = curProc->Memory[data.off + 1];

	if (op1.Memory_u > op2.Memory_u)
		curProc->flags.OF = 1;
	else if (op1.Memory_u < op2.Memory_u)
		curProc->flags.OF = -1;
	else
		curProc->flags.OF = 0;
}

Transference::Transference(Processor &_curProc)
	: Command(_curProc)
{}

void Transference::execute()
{
	if (data.type == 16) RR();
	else if (data.type == 79) AR();
	else if (data.type == 80) RA();
}

void Transference::RR()
{
	curProc->GPR[data.r2].Memory_i = curProc->GPR[data.r1].Memory_i;

	if (data.s == 1)
		curProc->GPR[data.r2 + 1].Memory_i = curProc->GPR[data.r1 + 1].Memory_i;
}

void Transference::AR()
{
	curProc->GPR[data.r2].d[0] = curProc->Memory[data.off];
	curProc->GPR[data.r2].d[1] = curProc->Memory[data.off + 1];

	if (data.s == 1)
	{ 
		curProc->GPR[data.r2 + 1].d[0] = curProc->Memory[data.off + 2];
		curProc->GPR[data.r2 + 1].d[1] = curProc->Memory[data.off + 3];
	}
}

void Transference::RA()
{
	curProc->Memory[data.off] = curProc->GPR[data.r2].d[0];
	curProc->Memory[data.off + 1] = curProc->GPR[data.r2].d[1];
	
	if (data.s == 1)
	{
		curProc->Memory[data.off + 2] = curProc->GPR[data.r1 + 1].d[0];
		curProc->Memory[data.off + 3] = curProc->GPR[data.r1 + 1].d[0];
	}
}

Jump::Jump(Processor &_curProc)
	: Command(_curProc)
{
}

void Jump::execute()
{
	go();
}

void Jump::go()
{
	curProc->setIP(data.off);
}

JumpReq::JumpReq(Processor &_curProc)
	: Jump(_curProc)
{
}

void JumpReq::execute()
{
	//if (data.type == 16) RR();
	//else if (data.type == 80) RA();
}