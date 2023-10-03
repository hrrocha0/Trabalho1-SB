#ifndef TRABALHO1_SB_MONTADOR_FIRST_PASS_H_
#define TRABALHO1_SB_MONTADOR_FIRST_PASS_H_

#include <vector>
#include <map>
#include <string>

/**
 * Executa a primeira passagem do montador, lendo o código e atualizando a tabela de símbolos.
 * @param lines - as linhas de código.
 * @param instructionTable - a tabela de instruções.
 * @param directiveTable - a tabela de diretivas.
 * @param symbolTable  - a tabela de símbolos.
 */
void first_pass(
	const std::vector<std::string>& lines,
	const std::map<std::string, std::pair<int, int>>& instructionTable,
	const std::map<std::string, int>& directiveTable,
	std::map<std::string, int>& symbolTable
);

#endif //TRABALHO1_SB_MONTADOR_FIRST_PASS_H_
