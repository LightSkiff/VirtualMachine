#ifndef LAYOUT_H
#define LAYOUT_H

//���������� ����� � 16,7 �����.
const int Bit7 = 128;
const int Bit16 = 65536;

//��������� ��� ������� ����������.
const int wrong_file = -1;
const int wrong_length = -2;
const int wrong_data = -3;

typedef unsigned short Address;
typedef unsigned char Byte;

//��������� ��� �������� ������ � ����� ����.
struct Command32Bit
{
	unsigned char type : 7;
	unsigned char s : 1;
	unsigned char r1 : 4;
	unsigned char r2 : 4;
	Address off;
};

//��������� ��� �������� ������ � ������ � � ���.
union DataInt
{
	Byte d[2];
	short Memory_i;
};
union DataUint
{
	Byte d[2];
	unsigned short Memory_u;
};
union DataFloat
{
	Byte d[4];
	float Memory_f;
};
union DataCommand32Bit
{
	Byte d[4];
	Command32Bit cmd;
};
union DataGPR
{
	Byte d[2];
	short Memory_i;
	unsigned short Memory_u;
};

#endif