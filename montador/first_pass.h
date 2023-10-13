#include <vector>
#include <string>
#include "InstructionTable.h"
#include "SymbolTable.h"

#ifndef TRABALHO1_SB_MONTADOR_FIRST_PASS_H_
#define TRABALHO1_SB_MONTADOR_FIRST_PASS_H_

/**
 * Executa a primeira passagem do algoritmo de duas passagens do montador. Armazena os rótulos
 * e seus respectivos endereços na tabela de símbolos.
 * @param lines - as linhas do código fonte.
 * @param symbolTable - uma referência à tabela de símbolos.
 * @param instructionTable - a tabela de instruções.
 * @return true, se não houveram erros, false, caso contrário.
 */
bool first_pass(
	const std::vector<std::string>& lines,
	SymbolTable& symbolTable,
	InstructionTable instructionTable
);

#endif //TRABALHO1_SB_MONTADOR_FIRST_PASS_H_
