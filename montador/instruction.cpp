#include "instruction.h"
#include <sstream>

using namespace std;

string uppercase(const string& s);

Instruction get_instruction(const string& line)
{
	Instruction instruction;
	istringstream stream(line);
	string token;

	while (getline(stream, token, ' '))
	{
		if (token.empty())
			continue;
		if (token.front() == ';')
			break;
		if (token.back() == ':')
		{
			token.pop_back();
			instruction.label = uppercase(token);
			continue;
		}
		if (instruction.operation.empty())
		{
			instruction.operation = uppercase(token);
			continue;
		}
		instruction.operands.push_back(uppercase(token));
	}
	return instruction;
}

string uppercase(const string& s)
{
	string newString;

	for (char c : s)
	{
		newString.push_back((char)toupper(c));
	}
	return newString;
}
