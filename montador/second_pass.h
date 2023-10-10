#include <vector>
#include <string>
#include "InstructionTable.h"
#include "SymbolTable.h"

#ifndef TRABALHO1_SB_MONTADOR_SECOND_PASS_H_
#define TRABALHO1_SB_MONTADOR_SECOND_PASS_H_

bool second_pass(
	const std::vector<std::string>& lines,
	std::vector<int>& objectCode,
	SymbolTable symbolTable,
	InstructionTable instructionTable
);

#endif //TRABALHO1_SB_MONTADOR_SECOND_PASS_H_
