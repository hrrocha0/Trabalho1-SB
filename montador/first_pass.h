#include <vector>
#include <string>
#include "InstructionTable.h"
#include "SymbolTable.h"

#ifndef TRABALHO1_SB_MONTADOR_FIRST_PASS_H_
#define TRABALHO1_SB_MONTADOR_FIRST_PASS_H_

bool first_pass(
	const std::vector<std::string>& lines,
	SymbolTable& symbolTable,
	InstructionTable instructionTable
);

#endif //TRABALHO1_SB_MONTADOR_FIRST_PASS_H_
