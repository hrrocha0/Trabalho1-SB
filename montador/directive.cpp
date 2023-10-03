#include "directive.h"

using namespace std;

int run_directive(int directive, const Instruction& instruction)
{
	switch (directive)
	{
	case 0:
		return 0;
	case 1:
		return instruction.operands.empty() ? 1 : stoi(instruction.operands[0]);
	case 2:
		return 1;
	default:
		return 0;
	}
}
