#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <sstream>

#include "layout.h"

using namespace std;

void load(const string &filename, Byte *memory, Address &ip);

void parseHead(const string &loadLine, Address &ip);
void parseLine(const string &line, Byte *memory, Address &ip);

void safeShort(stringstream &stream, Byte *memory);
void safeUShort(stringstream &stream, Byte *memory);
void safeFloat(stringstream &stream, Byte *memory);
void safeAddress(stringstream &stream, Byte *memory);
void safeCommand(stringstream &stream, Byte *memory, Address &ip);
void safeStop(stringstream &stream, Byte *memory, Address &ip);
void safeReturn(stringstream &stream, Byte *memory, Address &ip);

#endif