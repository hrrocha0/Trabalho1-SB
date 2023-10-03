#include "first_pass.h"
#include "instruction.h"
#include "directive.h"
#include <iostream>
#include <regex>

using namespace std;

void first_pass(
	const vector<string>& lines,
	const map<string, pair<int, int>>& instructionTable,
	const map<string, int>& directiveTable,
	map<string, int>& symbolTable
)
{
	int locationCounter = 0, lineCounter = 1;
	regex labelRegex(R"([A-Za-z_][A-Za-z0-9_]{0,29})");

	for (const auto& line : lines)
	{
		auto instruction = get_instruction(line);

		if (!instruction.label.empty())
		{
			const auto& label = instruction.label;

			if (!regex_match(label, labelRegex))
			{
				cerr << "ERRO LEXICO" << endl;
				lineCounter++;

				continue;
			}
			if (symbolTable.count(label))
			{
				cerr << "ERRO SEMANTICO" << endl;
				lineCounter++;

				continue;
			}
			symbolTable[label] = locationCounter;
		}
		if (instruction.operation.empty())
		{
			lineCounter++;
			continue;
		}
		const auto& operation = instruction.operation;

		if (instructionTable.count(operation))
		{
			int length = instructionTable.at(operation).second;

			locationCounter += length;
			lineCounter++;

			continue;
		}
		if (directiveTable.count(operation))
		{
			int directive = directiveTable.at(operation);
			int length = run_directive(directive, instruction);

			locationCounter += length;
			lineCounter++;

			continue;
		}
		cerr << "ERRO SINTATICO" << endl;
		lineCounter++;
	}
}
