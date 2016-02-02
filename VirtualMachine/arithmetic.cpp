#include "command.h"

Arithmetic::Arithmetic(Processor &_curProc)
	: Command(_curProc)
{
}

void Arithmetic::execute()
{
	if ((data.type == 2) || (data.type == 4) || (data.type == 6) || (data.type == 8)) R();
	else if ((data.type == 65) || (data.type == 67) || (data.type == 69) || (data.type == 71)) A();
	else if ((data.type == 3) || (data.type == 5) || (data.type == 7) || (data.type == 9))  UR();
	else if ((data.type == 66) || (data.type == 68) || (data.type == 70) || (data.type == 72)) UA();
}

void Arithmetic::R()
{
	if (data.s == 0)
	{
		DataInt op1;
		DataInt op2;
		DataInt res;

		op1.Memory_i = curProc->GPR[data.r1].Memory_i;
		op2.Memory_i = curProc->GPR[data.r2].Memory_i;


		if ((operationI(op1.Memory_i, op2.Memory_i) > SHRT_MAX) || (operationI(op1.Memory_i, op2.Memory_i) < SHRT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_i = operationI(op1.Memory_i, op2.Memory_i);
			curProc->GPR[data.r2].Memory_i = res.Memory_i;
			curProc->flags.OF = 0;
		}
	}
	else
	{
		DataFloat op1;
		DataFloat op2;
		DataFloat res;

		op1.d[0] = curProc->GPR[data.r1].d[0];
		op1.d[1] = curProc->GPR[data.r1].d[1];
		op1.d[2] = curProc->GPR[data.r1 + 1].d[0];
		op1.d[3] = curProc->GPR[data.r1 + 1].d[1];
		op2.d[0] = curProc->GPR[data.r2].d[0];
		op2.d[1] = curProc->GPR[data.r2].d[1];
		op2.d[2] = curProc->GPR[data.r2 + 1].d[0];
		op2.d[3] = curProc->GPR[data.r2 + 1].d[1];

		if ((operationF(op1.Memory_f, op2.Memory_f) > FLT_MAX) || (operationF(op1.Memory_f, op2.Memory_f) < FLT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_f = operationF(op1.Memory_f, op2.Memory_f);

			curProc->GPR[data.r2].d[0] = res.d[0];
			curProc->GPR[data.r2].d[1] = res.d[1];
			curProc->GPR[data.r2 + 1].d[0] = res.d[2];
			curProc->GPR[data.r2 + 1].d[1] = res.d[3];

			curProc->flags.OF = 0;
		}
	}
}

void Arithmetic::A()
{
	if (data.s == 0)
	{
		DataInt op1;
		DataInt op2;
		DataInt res;

		op1.Memory_i = curProc->GPR[data.r1].Memory_i;
		op2.d[0] = curProc->Memory[data.off];
		op2.d[1] = curProc->Memory[data.off + 1];

		if (((op1.Memory_i + op2.Memory_i) > SHRT_MAX) || ((op1.Memory_i + op2.Memory_i) < SHRT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_i = op1.Memory_i + op2.Memory_i;

			curProc->Memory[data.off] = res.d[0];
			curProc->Memory[data.off + 1] = res.d[1];

			curProc->flags.OF = 0;
		}
	}
	else
	{
		DataFloat op1;
		DataFloat op2;
		DataFloat res;

		op1.d[0] = curProc->GPR[data.r1].d[0];
		op1.d[1] = curProc->GPR[data.r1].d[1];
		op1.d[2] = curProc->GPR[data.r1 + 1].d[0];
		op1.d[3] = curProc->GPR[data.r1 + 1].d[1];
		op2.d[0] = curProc->Memory[data.off];
		op2.d[1] = curProc->Memory[data.off + 1];
		op2.d[2] = curProc->Memory[data.off + 2];
		op2.d[3] = curProc->Memory[data.off + 3];

		if ((operationF(op1.Memory_f, op2.Memory_f) > FLT_MAX) || (operationF(op1.Memory_f, op2.Memory_f) < FLT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_f = operationF(op1.Memory_f, op2.Memory_f);

			curProc->Memory[data.off] = res.d[0];
			curProc->Memory[data.off + 1] = res.d[1];
			curProc->Memory[data.off + 2] = res.d[2];
			curProc->Memory[data.off + 3] = res.d[3];

			curProc->flags.OF = 0;
		}
	}
}

void Arithmetic::UR()
{
	DataUint op1;
	DataUint op2;
	DataUint res;

	op1.Memory_u = curProc->GPR[data.r1].Memory_u;
	op2.Memory_u = curProc->GPR[data.r2].Memory_u;

	if ((operationU(op1.Memory_u, op2.Memory_u) > USHRT_MAX) || (operationU(op1.Memory_u, op2.Memory_u) < 0))
	{
		curProc->flags.OF = 1;
	}
	else
	{
		res.Memory_u = operationU(op1.Memory_u, op2.Memory_u);
		curProc->GPR[data.r2].Memory_u = res.Memory_u;
		curProc->flags.OF = 0;
	}
}

void Arithmetic::UA()
{
	DataUint op1;
	DataUint op2;
	DataUint res;

	op1.Memory_u = curProc->GPR[data.r1].Memory_u;
	op2.d[0] = curProc->Memory[data.off];
	op2.d[1] = curProc->Memory[data.off + 1];

	if ((operationU(op1.Memory_u, op2.Memory_u) > USHRT_MAX) || (operationU(op1.Memory_u, op2.Memory_u) < 0))
	{
		curProc->flags.OF = 1;
	}
	else
	{
		res.Memory_u = operationU(op1.Memory_u, op2.Memory_u);

		curProc->Memory[data.off] = res.d[0];
		curProc->Memory[data.off + 1] = res.d[1];

		curProc->flags.OF = 0;
	}
}

Summation::Summation(Processor &_curProc)
	: Arithmetic(_curProc)
{
}

short Summation::operationI(short op1, short op2)
{
	return op1 + op2;
}

unsigned short Summation::operationU(unsigned short op1, unsigned short op2)
{
	return op1 + op2;
}

float Summation::operationF(float op1, float op2)
{
	return op1 + op2;
}

Subtraction::Subtraction(Processor &_curProc)
	: Arithmetic(_curProc)
{
}

short Subtraction::operationI(short op1, short op2)
{
	return op1 - op2;
}

unsigned short Subtraction::operationU(unsigned short op1, unsigned short op2)
{
	return op1 - op2;
}
float Subtraction::operationF(float op1, float op2)
{
	return op1 - op2;
}

Multiplication::Multiplication(Processor &_curProc)
	: Arithmetic(_curProc)
{
}

short Multiplication::operationI(short op1, short op2)
{
	return op1 * op2;
}

unsigned short Multiplication::operationU(unsigned short op1, unsigned short op2)
{
	return op1 * op2;
}

float Multiplication::operationF(float op1, float op2)
{
	return op1 * op2;
}

Division::Division(Processor &_curProc)
	: Arithmetic(_curProc)
{
}

short Division::operationI(short op1, short op2)
{
	return op1 / op2;
}

unsigned short Division::operationU(unsigned short op1, unsigned short op2)
{
	return op1 / op2;
}

float Division::operationF(float op1, float op2)
{
	return op1 / op2;
}

/*Summation::Summation(Processor *_curProc)
	: Command(_curProc)
{
}

void Summation::execute()
{
	if (data.type == 2) R();
	else if (data.type == 65) A();
	else if (data.type == 3)  UR();
	else if (data.type == 66) UA();
}

void Summation::R()
{
	if (data.s == 0)
	{
		DataInt op1;
		DataInt op2;
		DataInt res;

		op1.Memory_i = curProc->GPR[data.r1].Memory_i;
		op2.Memory_i = curProc->GPR[data.r2].Memory_i;


		if (((op1.Memory_i + op2.Memory_i) > SHRT_MAX) || ((op1.Memory_i + op2.Memory_i) < SHRT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_i = op1.Memory_i + op2.Memory_i;
			curProc->GPR[data.r2].Memory_i = res.Memory_i;
			curProc->flags.OF = 0;
		}
	}
	else
	{
		DataFloat op1;
		DataFloat op2;
		DataFloat res;

		op1.d[0] = curProc->GPR[data.r1].d[0];
		op1.d[1] = curProc->GPR[data.r1].d[1];
		op1.d[2] = curProc->GPR[data.r1 + 1].d[0];
		op1.d[3] = curProc->GPR[data.r1 + 1].d[1];
		op2.d[0] = curProc->GPR[data.r2].d[0];
		op2.d[1] = curProc->GPR[data.r2].d[1];
		op2.d[2] = curProc->GPR[data.r2 + 1].d[0];
		op2.d[3] = curProc->GPR[data.r2 + 1].d[1];

		if (((op1.Memory_f + op2.Memory_f) > FLT_MAX) || ((op1.Memory_f + op2.Memory_f) < FLT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_f = op1.Memory_f + op2.Memory_f;

			curProc->GPR[data.r2].d[0] = res.d[0];
			curProc->GPR[data.r2].d[1] = res.d[1];
			curProc->GPR[data.r2 + 1].d[0] = res.d[2];
			curProc->GPR[data.r2 + 1].d[1] = res.d[3];

			curProc->flags.OF = 0;
		}
	}
}

void Summation::A()
{
	if (data.s == 0)
	{
		DataInt op1;
		DataInt op2;
		DataInt res;

		op1.Memory_i = curProc->GPR[data.r1].Memory_i;
		op2.d[0] = curProc->Memory[data.off];
		op2.d[1] = curProc->Memory[data.off + 1];

		if (((op1.Memory_i + op2.Memory_i) > SHRT_MAX) || ((op1.Memory_i + op2.Memory_i) < SHRT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_i = op1.Memory_i + op2.Memory_i;

			curProc->Memory[data.off] = res.d[0];
			curProc->Memory[data.off + 1] = res.d[1];

			curProc->flags.OF = 0;
		}
	}
	else
	{
		DataFloat op1;
		DataFloat op2;
		DataFloat res;

		op1.d[0] = curProc->GPR[data.r1].d[0];
		op1.d[1] = curProc->GPR[data.r1].d[1];
		op1.d[2] = curProc->GPR[data.r1 + 1].d[0];
		op1.d[3] = curProc->GPR[data.r1 + 1].d[1];
		op2.d[0] = curProc->Memory[data.off];
		op2.d[1] = curProc->Memory[data.off + 1];
		op2.d[2] = curProc->Memory[data.off + 2];
		op2.d[3] = curProc->Memory[data.off + 3];

		if (((op1.Memory_f + op2.Memory_f) > FLT_MAX) || ((op1.Memory_f + op2.Memory_f) < FLT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_f = op1.Memory_f + op2.Memory_f;

			curProc->Memory[data.off] = res.d[0];
			curProc->Memory[data.off + 1] = res.d[1];
			curProc->Memory[data.off + 2] = res.d[2];
			curProc->Memory[data.off + 3] = res.d[3];

			curProc->flags.OF = 0;
		}
	}
}

void Summation::UR()
{
	DataUint op1;
	DataUint op2;
	DataUint res;

	op1.Memory_u = curProc->GPR[data.r1].Memory_u;
	op2.Memory_u = curProc->GPR[data.r2].Memory_u;

	if (((op1.Memory_u + op2.Memory_u) > USHRT_MAX) || ((op1.Memory_u + op2.Memory_u) < 0))
	{
		curProc->flags.OF = 1;
	}
	else
	{
		res.Memory_u = op1.Memory_u + op2.Memory_u;
		curProc->GPR[data.r2].Memory_u = res.Memory_u;
		curProc->flags.OF = 0;
	}
}

void Summation::UA()
{
	DataUint op1;
	DataUint op2;
	DataUint res;

	op1.Memory_u = curProc->GPR[data.r1].Memory_u;
	op2.d[0] = curProc->Memory[data.off];
	op2.d[1] = curProc->Memory[data.off + 1];

	if (((op1.Memory_u + op2.Memory_u) > USHRT_MAX) || ((op1.Memory_u + op2.Memory_u) < 0))
	{
		curProc->flags.OF = 1;
	}
	else
	{
		res.Memory_u = op1.Memory_u + op2.Memory_u;

		curProc->Memory[data.off] = res.d[0];
		curProc->Memory[data.off + 1] = res.d[1];

		curProc->flags.OF = 0;
	}
}


Subtraction::Subtraction(Processor *_curProc)
	: Command(_curProc)
{
}

void Subtraction::execute()
{
	if (data.type == 4) R();
	else if (data.type == 67) A();
	else if (data.type == 5)  UR();
	else if (data.type == 68) UA();
}

void Subtraction::R()
{
	if (data.s == 0)
	{
		DataInt op1;
		DataInt op2;
		DataInt res;

		op1.Memory_i = curProc->GPR[data.r1].Memory_i;
		op2.Memory_i = curProc->GPR[data.r2].Memory_i;


		if (((op1.Memory_i - op2.Memory_i) > SHRT_MAX) || ((op1.Memory_i - op2.Memory_i) < SHRT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_i = op1.Memory_i - op2.Memory_i;
			curProc->GPR[data.r2].Memory_i = res.Memory_i;
			curProc->flags.OF = 0;
		}
	}
	else
	{
		DataFloat op1;
		DataFloat op2;
		DataFloat res;

		op1.d[0] = curProc->GPR[data.r1].d[0];
		op1.d[1] = curProc->GPR[data.r1].d[1];
		op1.d[2] = curProc->GPR[data.r1 + 1].d[0];
		op1.d[3] = curProc->GPR[data.r1 + 1].d[1];
		op2.d[0] = curProc->GPR[data.r2].d[0];
		op2.d[1] = curProc->GPR[data.r2].d[1];
		op2.d[2] = curProc->GPR[data.r2 + 1].d[0];
		op2.d[3] = curProc->GPR[data.r2 + 1].d[1];

		if (((op1.Memory_f - op2.Memory_f) > FLT_MAX) || ((op1.Memory_f - op2.Memory_f) < FLT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_f = op1.Memory_f - op2.Memory_f;

			curProc->GPR[data.r2].d[0] = res.d[0];
			curProc->GPR[data.r2].d[1] = res.d[1];
			curProc->GPR[data.r2 + 1].d[0] = res.d[2];
			curProc->GPR[data.r2 + 1].d[1] = res.d[3];

			curProc->flags.OF = 0;
		}
	}
}

void Subtraction::A()
{
	if (data.s == 0)
	{
		DataInt op1;
		DataInt op2;
		DataInt res;

		op1.Memory_i = curProc->GPR[data.r1].Memory_i;
		op2.d[0] = curProc->Memory[data.off];
		op2.d[1] = curProc->Memory[data.off + 1];

		if (((op1.Memory_i - op2.Memory_i) > SHRT_MAX) || ((op1.Memory_i - op2.Memory_i) < SHRT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_i = op1.Memory_i - op2.Memory_i;

			curProc->Memory[data.off] = res.d[0];
			curProc->Memory[data.off + 1] = res.d[1];

			curProc->flags.OF = 0;
		}
	}
	else
	{
		DataFloat op1;
		DataFloat op2;
		DataFloat res;

		op1.d[0] = curProc->GPR[data.r1].d[0];
		op1.d[1] = curProc->GPR[data.r1].d[1];
		op1.d[2] = curProc->GPR[data.r1 + 1].d[0];
		op1.d[3] = curProc->GPR[data.r1 + 1].d[1];
		op2.d[0] = curProc->Memory[data.off];
		op2.d[1] = curProc->Memory[data.off + 1];
		op2.d[2] = curProc->Memory[data.off + 2];
		op2.d[3] = curProc->Memory[data.off + 3];

		if (((op1.Memory_f - op2.Memory_f) > FLT_MAX) || ((op1.Memory_f - op2.Memory_f) < FLT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_f = op1.Memory_f - op2.Memory_f;

			curProc->Memory[data.off] = res.d[0];
			curProc->Memory[data.off + 1] = res.d[1];
			curProc->Memory[data.off + 2] = res.d[2];
			curProc->Memory[data.off + 3] = res.d[3];

			curProc->flags.OF = 0;
		}
	}
}

void Subtraction::UR()
{
	DataUint op1;
	DataUint op2;
	DataUint res;

	op1.Memory_u = curProc->GPR[data.r1].Memory_u;
	op2.Memory_u = curProc->GPR[data.r2].Memory_u;

	if (((op1.Memory_u - op2.Memory_u) > USHRT_MAX) || ((op1.Memory_u - op2.Memory_u) < 0))
	{
		curProc->flags.OF = 1;
	}
	else
	{
		res.Memory_u = op1.Memory_u - op2.Memory_u;
		curProc->GPR[data.r2].Memory_u = res.Memory_u;
		curProc->flags.OF = 0;
	}
}

void Subtraction::UA()
{
	DataUint op1;
	DataUint op2;
	DataUint res;

	op1.Memory_u = curProc->GPR[data.r1].Memory_u;
	op2.d[0] = curProc->Memory[data.off];
	op2.d[1] = curProc->Memory[data.off + 1];

	if (((op1.Memory_u - op2.Memory_u) > USHRT_MAX) || ((op1.Memory_u - op2.Memory_u) < 0))
	{
		curProc->flags.OF = 1;
	}
	else
	{
		res.Memory_u = op1.Memory_u - op2.Memory_u;

		curProc->Memory[data.off] = res.d[0];
		curProc->Memory[data.off + 1] = res.d[1];

		curProc->flags.OF = 0;
	}
}

Multiplication::Multiplication(Processor *_curProc)
	: Command(_curProc)
{
}

void Multiplication::execute()
{
	if (data.type == 6) R();
	else if (data.type == 69) A();
	else if (data.type == 7)  UR();
	else if (data.type == 70) UA();
}

void Multiplication::R()
{
	if (data.s == 0)
	{
		DataInt op1;
		DataInt op2;
		DataInt res;

		op1.Memory_i = curProc->GPR[data.r1].Memory_i;
		op2.Memory_i = curProc->GPR[data.r2].Memory_i;


		if (((op1.Memory_i * op2.Memory_i) > SHRT_MAX) || ((op1.Memory_i * op2.Memory_i) < SHRT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_i = op1.Memory_i * op2.Memory_i;
			curProc->GPR[data.r2].Memory_i = res.Memory_i;
			curProc->flags.OF = 0;
		}
	}
	else
	{
		DataFloat op1;
		DataFloat op2;
		DataFloat res;

		op1.d[0] = curProc->GPR[data.r1].d[0];
		op1.d[1] = curProc->GPR[data.r1].d[1];
		op1.d[2] = curProc->GPR[data.r1 + 1].d[0];
		op1.d[3] = curProc->GPR[data.r1 + 1].d[1];
		op2.d[0] = curProc->GPR[data.r2].d[0];
		op2.d[1] = curProc->GPR[data.r2].d[1];
		op2.d[2] = curProc->GPR[data.r2 + 1].d[0];
		op2.d[3] = curProc->GPR[data.r2 + 1].d[1];

		if (((op1.Memory_f * op2.Memory_f) > FLT_MAX) || ((op1.Memory_f * op2.Memory_f) < FLT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_f = op1.Memory_f * op2.Memory_f;

			curProc->GPR[data.r2].d[0] = res.d[0];
			curProc->GPR[data.r2].d[1] = res.d[1];
			curProc->GPR[data.r2 + 1].d[0] = res.d[2];
			curProc->GPR[data.r2 + 1].d[1] = res.d[3];

			curProc->flags.OF = 0;
		}
	}
}

void Multiplication::A()
{
	if (data.s == 0)
	{
		DataInt op1;
		DataInt op2;
		DataInt res;

		op1.Memory_i = curProc->GPR[data.r1].Memory_i;
		op2.d[0] = curProc->Memory[data.off];
		op2.d[1] = curProc->Memory[data.off + 1];

		if (((op1.Memory_i * op2.Memory_i) > SHRT_MAX) || ((op1.Memory_i * op2.Memory_i) < SHRT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_i = op1.Memory_i * op2.Memory_i;

			curProc->Memory[data.off] = res.d[0];
			curProc->Memory[data.off + 1] = res.d[1];

			curProc->flags.OF = 0;
		}
	}
	else
	{
		DataFloat op1;
		DataFloat op2;
		DataFloat res;

		op1.d[0] = curProc->GPR[data.r1].d[0];
		op1.d[1] = curProc->GPR[data.r1].d[1];
		op1.d[2] = curProc->GPR[data.r1 + 1].d[0];
		op1.d[3] = curProc->GPR[data.r1 + 1].d[1];
		op2.d[0] = curProc->Memory[data.off];
		op2.d[1] = curProc->Memory[data.off + 1];
		op2.d[2] = curProc->Memory[data.off + 2];
		op2.d[3] = curProc->Memory[data.off + 3];

		if (((op1.Memory_f * op2.Memory_f) > FLT_MAX) || ((op1.Memory_f * op2.Memory_f) < FLT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_f = op1.Memory_f * op2.Memory_f;

			curProc->Memory[data.off] = res.d[0];
			curProc->Memory[data.off + 1] = res.d[1];
			curProc->Memory[data.off + 2] = res.d[2];
			curProc->Memory[data.off + 3] = res.d[3];

			curProc->flags.OF = 0;
		}
	}
}

void Multiplication::UR()
{
	DataUint op1;
	DataUint op2;
	DataUint res;

	op1.Memory_u = curProc->GPR[data.r1].Memory_u;
	op2.Memory_u = curProc->GPR[data.r2].Memory_u;

	if (((op1.Memory_u * op2.Memory_u) > USHRT_MAX) || ((op1.Memory_u * op2.Memory_u) < 0))
	{
		curProc->flags.OF = 1;
	}
	else
	{
		res.Memory_u = op1.Memory_u * op2.Memory_u;
		curProc->GPR[data.r2].Memory_u = res.Memory_u;
		curProc->flags.OF = 0;
	}
}

void Multiplication::UA()
{
	DataUint op1;
	DataUint op2;
	DataUint res;

	op1.Memory_u = curProc->GPR[data.r1].Memory_u;
	op2.d[0] = curProc->Memory[data.off];
	op2.d[1] = curProc->Memory[data.off + 1];

	if (((op1.Memory_u * op2.Memory_u) > USHRT_MAX) || ((op1.Memory_u * op2.Memory_u) < 0))
	{
		curProc->flags.OF = 1;
	}
	else
	{
		res.Memory_u = op1.Memory_u * op2.Memory_u;

		curProc->Memory[data.off] = res.d[0];
		curProc->Memory[data.off + 1] = res.d[1];

		curProc->flags.OF = 0;
	}
}

Division::Division(Processor *_curProc)
	: Command(_curProc)
{
}

void Division::execute()
{
	if (data.type == 8) R();
	else if (data.type == 71) A();
	else if (data.type == 9)  UR();
	else if (data.type == 72) UA();
}

void Division::R()
{
	if (data.s == 0)
	{
		DataInt op1;
		DataInt op2;
		DataInt res;

		op1.Memory_i = curProc->GPR[data.r1].Memory_i;
		op2.Memory_i = curProc->GPR[data.r2].Memory_i;

		res.Memory_i = op1.Memory_i / op2.Memory_i;

		curProc->GPR[data.r2].Memory_i = res.Memory_i;
		curProc->flags.OF = 0;
	}
	else
	{
		DataFloat op1;
		DataFloat op2;
		DataFloat res;

		op1.d[0] = curProc->GPR[data.r1].d[0];
		op1.d[1] = curProc->GPR[data.r1].d[1];
		op1.d[2] = curProc->GPR[data.r1 + 1].d[0];
		op1.d[3] = curProc->GPR[data.r1 + 1].d[1];
		op2.d[0] = curProc->GPR[data.r2].d[0];
		op2.d[1] = curProc->GPR[data.r2].d[1];
		op2.d[2] = curProc->GPR[data.r2 + 1].d[0];
		op2.d[3] = curProc->GPR[data.r2 + 1].d[1];

		if (((op1.Memory_f / op2.Memory_f) > FLT_MAX) || ((op1.Memory_f / op2.Memory_f) < FLT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_f = op1.Memory_f / op2.Memory_f;

			curProc->GPR[data.r2].d[0] = res.d[0];
			curProc->GPR[data.r2].d[1] = res.d[1];
			curProc->GPR[data.r2 + 1].d[0] = res.d[2];
			curProc->GPR[data.r2 + 1].d[1] = res.d[3];

			curProc->flags.OF = 0;
		}
	}
}

void Division::A()
{
	if (data.s == 0)
	{
		DataInt op1;
		DataInt op2;
		DataInt res;

		op1.Memory_i = curProc->GPR[data.r1].Memory_i;
		op2.d[0] = curProc->Memory[data.off];
		op2.d[1] = curProc->Memory[data.off + 1];

		res.Memory_i = op1.Memory_i / op2.Memory_i;

		curProc->Memory[data.off] = res.d[0];
		curProc->Memory[data.off + 1] = res.d[1];

		curProc->flags.OF = 0;
	}
	else
	{
		DataFloat op1;
		DataFloat op2;
		DataFloat res;

		op1.d[0] = curProc->GPR[data.r1].d[0];
		op1.d[1] = curProc->GPR[data.r1].d[1];
		op1.d[2] = curProc->GPR[data.r1 + 1].d[0];
		op1.d[3] = curProc->GPR[data.r1 + 1].d[1];
		op2.d[0] = curProc->Memory[data.off];
		op2.d[1] = curProc->Memory[data.off + 1];
		op2.d[2] = curProc->Memory[data.off + 2];
		op2.d[3] = curProc->Memory[data.off + 3];

		if (((op1.Memory_f / op2.Memory_f) > FLT_MAX) || ((op1.Memory_f / op2.Memory_f) < FLT_MIN))
		{
			curProc->flags.OF = 1;
		}
		else
		{
			res.Memory_f = op1.Memory_f / op2.Memory_f;

			curProc->Memory[data.off] = res.d[0];
			curProc->Memory[data.off + 1] = res.d[1];
			curProc->Memory[data.off + 2] = res.d[2];
			curProc->Memory[data.off + 3] = res.d[3];

			curProc->flags.OF = 0;
		}
	}
}

void Division::UR()
{
	DataUint op1;
	DataUint op2;
	DataUint res;

	op1.Memory_u = curProc->GPR[data.r1].Memory_u;
	op2.Memory_u = curProc->GPR[data.r2].Memory_u;

	res.Memory_u = op1.Memory_u / op2.Memory_u;

	curProc->GPR[data.r2].Memory_u = res.Memory_u;
	curProc->flags.OF = 0;
}

void Division::UA()
{
	DataUint op1;
	DataUint op2;
	DataUint res;

	op1.Memory_u = curProc->GPR[data.r1].Memory_u;
	op2.d[0] = curProc->Memory[data.off];
	op2.d[1] = curProc->Memory[data.off + 1];

	res.Memory_u = op1.Memory_u / op2.Memory_u;

	curProc->Memory[data.off] = res.d[0];
	curProc->Memory[data.off + 1] = res.d[1];
	curProc->flags.OF = 0;
}*/

