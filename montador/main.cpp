#include "file.h"
#include "first_pass.h"
#include <iostream>
#include <map>

using namespace std;

typedef map<string, pair<int, int>> InstructionTable;
typedef map<string, int> DirectiveTable;
typedef map<string, int> SymbolTable;

int main(int argc, char* argv[])
{
	InstructionTable instructionTable{
		{ "ADD", { 1, 2 }},
		{ "SUB", { 2, 2 }},
		{ "MUL", { 3, 2 }},
		{ "DIV", { 4, 2 }},
		{ "JMP", { 5, 2 }},
		{ "JMPN", { 6, 2 }},
		{ "JMPP", { 7, 2 }},
		{ "JMPZ", { 8, 2 }},
		{ "COPY", { 9, 3 }},
		{ "LOAD", { 10, 2 }},
		{ "STORE", { 11, 2 }},
		{ "INPUT", { 12, 2 }},
		{ "OUTPUT", { 13, 2 }},
		{ "STOP", { 14, 1 }},
	};
	DirectiveTable directiveTable{
		{ "SECAO", 0 },
		{ "SPACE", 1 },
		{ "CONST", 2 },
	};
	SymbolTable symbolTable{};

	string path;
	vector<string> lines;

	if (argc < 2)
	{
		cerr << "CAMINHO NAO FORNECIDO" << endl;
		exit(1);
	}
	path = argv[1];
	lines = read_file(path);

	first_pass(lines, instructionTable, directiveTable, symbolTable);

	return 0;
}
