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

Instruction get_instruction(const std::string& line);

#endif //TRABALHO1_SB_MONTADOR_INSTRUCTION_H_
