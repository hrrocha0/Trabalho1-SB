#ifndef TRABALHO1_SB_MONTADOR_INSTRUCTION_H_
#define TRABALHO1_SB_MONTADOR_INSTRUCTION_H_

#include <vector>
#include <string>

typedef struct
{
	std::string label;
	std::string operation;
	std::vector<std::string> operands;
} Instruction;

/**
 * Obtém a partir de uma linha uma instrução assembly, separando em rótulo, operação e operandos.
 * Comentários, e espaços e tabulações em excesso são ignorados.
 * @param line - a linha com a instrução.
 * @return a instrução assembly.
 */
Instruction get_instruction(const std::string& line);

#endif //TRABALHO1_SB_MONTADOR_INSTRUCTION_H_
