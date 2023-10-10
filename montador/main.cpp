#include <iostream>
#include <vector>
#include "SymbolTable.h"
#include "InstructionTable.h"
#include "file.h"
#include "first_pass.h"
#include "second_pass.h"

/*
 * Software Básico (2023.2) - Trabalho 1
 * Henrique Rodrigues Rocha: 211036061
 */
int main(int argc, char* argv[])
{
	std::string path, filename;
	std::vector<std::string> lines;
	std::vector<int> objectCode;

	bool generateFile = true;

	SymbolTable symbolTable;
	InstructionTable instructionTable;

	instructionTable.add("ADD", 1, 2);
	instructionTable.add("SUB", 2, 2);
	instructionTable.add("MUL", 3, 2);
	instructionTable.add("DIV", 4, 2);
	instructionTable.add("JMP", 5, 2);
	instructionTable.add("JMPN", 6, 2);
	instructionTable.add("JMPP", 7, 2);
	instructionTable.add("JMPZ", 8, 2);
	instructionTable.add("COPY", 9, 3);
	instructionTable.add("LOAD", 10, 2);
	instructionTable.add("STORE", 11, 2);
	instructionTable.add("INPUT", 12, 2);
	instructionTable.add("OUTPUT", 13, 2);
	instructionTable.add("STOP", 14, 1);

	if (argc < 2)
	{
		std::cerr << "CAMINHO NAO FORNECIDO" << std::endl;
		abort();
	}
	path = argv[1];
	filename = get_filename(path);
	lines = read_file(path);

	generateFile &= first_pass(lines, symbolTable, instructionTable);
	generateFile &= second_pass(lines, objectCode, symbolTable, instructionTable);

	if (generateFile)
	{
		std::cout << "GENERATE FILE" << std::endl;
		write_file(filename, objectCode);
	}
	return 0;
}
