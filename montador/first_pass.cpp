#include "first_pass.h"
#include "instruction.h"
#include "directive.h"

using namespace std;

void first_pass(
	const vector<string>& lines,
	const map<string, pair<int, int>>& instructionTable,
	const map<string, int>& directiveTable,
	map<string, int>& symbolTable
)
{
	int locationCounter = 0, lineCounter = 1;

	for (const auto& line : lines)
	{
		auto instruction = get_instruction(line);

		if (!instruction.label.empty())
		{
			symbolTable[instruction.label] = locationCounter;
		}
		if (instruction.operation.empty())
		{
			lineCounter++;
			continue;
		}
		if (instructionTable.count(instruction.operation))
		{
			int length = instructionTable.at(instruction.operation).second;

			locationCounter += length;
			lineCounter++;

			continue;
		}
		if (directiveTable.count(instruction.operation))
		{
			int directive = directiveTable.at(instruction.operation);
			int length = run_directive(directive, instruction);

			locationCounter += length;
			lineCounter++;

			continue;
		}
		lineCounter++;
	}
}
