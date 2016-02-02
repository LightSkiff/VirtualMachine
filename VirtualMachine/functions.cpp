#include <fstream>
#include <sstream>

#include "prototypes.h"

using namespace std;

void load(const string &filename, Byte *memory, Address &ip)
{
	ifstream f(filename);
	Address copyIP;

	if (f.is_open())
	{
		string line;

		if (!f.eof())
		{
			ip = 0;
			while (ip == 0)
			{
				getline(f, line);
				parseHead(line, ip);
			}
			copyIP = ip;

			while (!f.eof())
			{
				getline(f, line);
				parseLine(line, memory, copyIP);
			}
		}
	}
	else
		throw wrong_file;
}

void parseHead(const string &loadLine, Address &ip)
{
	stringstream stream(loadLine);
	string tag;

	stream >> tag;

	if (tag == "IP")
	{
		Address loadAddress = 0;
		stream >> loadAddress;

		ip = loadAddress;

		if ((ip <= 0) || (ip > Bit16))
			throw wrong_length;
	}
	else
		ip = 0;
}

void parseLine(const string &line, Byte *memory, Address &ip)
{
	stringstream stream(line);
	string tag;

	stream >> tag;

	if (tag == "a") safeAddress(stream, memory);
	else if (tag == "i") safeShort(stream, memory);
	else if (tag == "u") safeUShort(stream, memory);
	else if (tag == "f") safeFloat(stream, memory);
	else if (tag == "k") safeCommand(stream, memory, ip);
	else if (tag == "stop") safeStop(stream, memory, ip);
	else if (tag == "return") safeReturn(stream, memory, ip);
}

void safeShort(stringstream& stream, Byte *memory)
{
	Address mp;
	stream >> mp;

	DataInt data; // Что положить
	stream >> data.Memory_i;

	if ((mp >= 0) && (mp < Bit16))
	{
		memory[mp] = data.d[0];
		memory[mp + 1] = data.d[1];
	}
	else
		throw wrong_length;
}

void safeUShort(stringstream& stream, Byte *memory)
{
	Address mp;
	stream >> mp;

	DataUint data;
	stream >> data.Memory_u;

	if ((mp >= 0) && (mp < Bit16))
	{
		memory[mp] = data.d[0];
		memory[mp + 1] = data.d[1];
	}
	else
		throw wrong_length;
}

void safeAddress(stringstream& stream, Byte* memory)
{
	safeUShort(stream, memory);
}

void safeFloat(std::stringstream& stream, Byte* memory)
{
	Address mp;
	stream >> mp;

	DataFloat data;
	stream >> data.Memory_f;

	if ((mp >= 0) && (mp < Bit16))
	{
		memory[mp] = data.d[0];
		memory[mp + 1] = data.d[1];
		memory[mp + 2] = data.d[2];
		memory[mp + 3] = data.d[3];
	}
	else
		throw wrong_length;
}

void safeCommand(std::stringstream& stream, Byte *memory, Address &ip)
{
	DataCommand32Bit data;

	DataInt tmp;

	stream >> tmp.Memory_i;
	data.cmd.type = tmp.Memory_i;

	stream >> tmp.Memory_i;
	data.cmd.s = tmp.Memory_i;

	stream >> tmp.Memory_i;
	data.cmd.r1 = tmp.Memory_i;

	stream >> tmp.Memory_i;
	data.cmd.r2 = tmp.Memory_i;

	if (data.cmd.type > 64)
	{
		stream >> tmp.Memory_i;
		data.cmd.off = tmp.Memory_i;

		if (ip < Bit16)
		{
			memory[ip++] = data.d[0];
			memory[ip++] = data.d[1];
			memory[ip++] = data.d[2];
			memory[ip++] = data.d[3];
		}
		else
			throw wrong_length;
	}
	else
	{
		if (ip < Bit16)
		{
			memory[ip++] = data.d[0];
			memory[ip++] = data.d[1];
		}
		else
			throw wrong_length;
	}
}

void safeStop(stringstream &stream, Byte *memory, Address &ip)
{
	DataCommand32Bit data;
	data.cmd.type = 1;
	data.cmd.s = 0;
	data.cmd.r1 = 0;
	data.cmd.r2 = 0;

	if (ip < Bit16)
	{
		memory[ip++] = data.d[0];
		memory[ip++] = data.d[1];
	}
	else
		throw wrong_length;
}

void safeReturn(stringstream &stream, Byte *memory, Address &ip)
{
	DataCommand32Bit data;
	data.cmd.type = 64;
	data.cmd.s = 0;
	data.cmd.r1 = 0;
	data.cmd.r2 = 0;

	if (ip < Bit16)
	{
		memory[ip++] = data.d[0];
		memory[ip++] = data.d[1];
	}
	else
		throw wrong_length;
}