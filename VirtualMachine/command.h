#ifndef COMMAND_H
#define COMMAND_H

#include "processor.h"
#include "layout.h"

class Processor;

class Command
{
	friend class Processor;

	public:
		Command(Processor &_curProc);
		void SetData(const Command32Bit &obj);
		void operator()();
		virtual void execute() = 0;
		~Command();

	protected:
		//Указатель на объект ВМ, вызвашей текущую команду.
		Processor *curProc;

		Command32Bit data;
};

class Compare : public Command
{
	public:
		Compare(Processor &_curProc);
		virtual void execute() override;

	private:
		void R();
		void A();
		void UR();
		void UA();
};

class Arithmetic : public Command
{
	public:
		Arithmetic(Processor &_curProc);
		virtual void execute() override;

	private:
		void R();
		void A();
		void UR();
		void UA();

		virtual short operationI(short op1, short op2) = 0;
		virtual unsigned short operationU(unsigned short op1, unsigned short op2) = 0;
		virtual float operationF(float op1, float op2) = 0;
};

class Summation : public Arithmetic
{
	public:
		Summation(Processor &_curProc);
		virtual short operationI(short op1, short op2) override;
		virtual unsigned short operationU(unsigned short op1, unsigned short op2) override;
		virtual float operationF(float op1, float op2) override;
};

class Subtraction : public Arithmetic
{
	public:
		Subtraction(Processor &_curProc);
		virtual short operationI(short op1, short op2) override;
		virtual unsigned short operationU(unsigned short op1, unsigned short op2) override;
		virtual float operationF(float op1, float op2) override;
};

class Multiplication : public Arithmetic
{
	public:
		Multiplication(Processor &_curProc);
		virtual short operationI(short op1, short op2) override;
		virtual unsigned short operationU(unsigned short op1, unsigned short op2) override;
		virtual float operationF(float op1, float op2) override;
};

class Division : public Arithmetic
{
	public:
		Division(Processor &_curProc);
		virtual short operationI(short op1, short op2) override;
		virtual unsigned short operationU(unsigned short op1, unsigned short op2) override;
		virtual float operationF(float op1, float op2) override;
};

class Out : public Command
{
	public:
		Out(Processor &_curProc);
		virtual void execute() override;

	private:
		void outR();
		void outUR();
		void outA();
		void outUA();
};

class Entry : public Command
{
	public:
		Entry(Processor &_curProc);
		virtual void execute() override;

	private:
		void entryR();
		void entryUR();
		void entryA();
		void entryUA();
};

class Transference : public Command
{
	public:
		Transference(Processor &_curProc);
		virtual void execute() override;

	private:
		void RR();
		void AR();
		void RA();	
};

class Jump : public Command
{
	public:
		Jump(Processor &_curProc);
		virtual void execute() override;

	private:
		void go();
};

class JumpReq : public Jump
{
	public:
		JumpReq(Processor &_curProc);
		virtual void execute() override;
};

#endif