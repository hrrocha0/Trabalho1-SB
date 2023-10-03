#include "instruction.h"
#include <sstream>

using namespace std;

Instruction get_instruction(const string& line)
{
	Instruction instruction;
	istringstream stream(line);
	string token;

	while (getline(stream, token, ' '))
	{
		if (token.front() == ';')
			break;
		if (token.back() == ':')
		{
			token.pop_back();
			instruction.label = token;
			continue;
		}
		if (instruction.operation.empty())
		{
			instruction.operation = token;
			continue;
		}
		instruction.operands.push_back(token);
	}
	return instruction;
}
