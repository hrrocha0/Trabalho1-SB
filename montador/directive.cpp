#include "directive.h"
#include <iostream>
#include <regex>

using namespace std;

int run_directive(int directive, const Instruction& instruction)
{
	regex spaceRegex(R"([0-9]+)"), constRegex(R"(\-?[0-9]+)");
	const auto& operands = instruction.operands;

	switch (directive)
	{
	case 0:
		if (operands.size() != 1)
		{
			cerr << "ERRO SINTATICO" << endl;
			return 0;
		}
		if (operands[0] != "DATA" && operands[0] != "TEXT")
		{
			cerr << "ERRO SINTATICO" << endl;
			return 0;
		}
		return 0;
	case 1:
		if (operands.empty())
			return 1;
		if (instruction.operands.size() != 1)
		{
			cerr << "ERRO SINTATICO" << endl;
			return 1;
		}
		if (!regex_match(operands[0], spaceRegex))
		{
			cerr << "ERRO LEXICO" << endl;
			return 1;
		}
		return stoi(operands[0]);
	case 2:
		if (instruction.operands.size() != 1)
		{
			cerr << "ERRO SINTATICO" << endl;
			return 1;
		}
		if (!regex_match(operands[0], constRegex))
		{
			cerr << "ERRO LEXICO" << endl;
		}
		return 1;
	default:
		return 0;
	}
}
