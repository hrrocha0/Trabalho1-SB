#include <vector>
#include <string>
#include "InstructionTable.h"
#include "SymbolTable.h"

#ifndef TRABALHO1_SB_MONTADOR_SECOND_PASS_H_
#define TRABALHO1_SB_MONTADOR_SECOND_PASS_H_

/**
 * Executa a segunda passagem do algoritmo de duas passagens do montador. Utiliza a tabela de
 * símbolos gerada pela primeira passagem para gerar o código objeto, que será armazenado em um
 * vetor.
 * @param lines - as linhas do código fonte.
 * @param objectCode - uma referência ao vetor que armazena o código objeto.
 * @param symbolTable - a tabela de símbolos.
 * @param instructionTable - a tabela de instruções.
 * @return true, se não houveram erros, false, caso contrário.
 */
bool second_pass(
	const std::vector<std::string>& lines,
	std::vector<int>& objectCode,
	SymbolTable symbolTable,
	InstructionTable instructionTable
);

#endif //TRABALHO1_SB_MONTADOR_SECOND_PASS_H_
