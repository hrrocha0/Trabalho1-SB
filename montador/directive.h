#ifndef TRABALHO1_SB_MONTADOR_DIRECTIVE_H_
#define TRABALHO1_SB_MONTADOR_DIRECTIVE_H_

#include "instruction.h"

/**
 * Executa uma diretiva.
 * @param directive - o código da diretiva a ser executada.
 * @param instruction - a instrução da diretiva.
 * @return o valor a ser adicionado ao contador de linhas.
 */
int run_directive(int directive, const Instruction& instruction);

#endif //TRABALHO1_SB_MONTADOR_DIRECTIVE_H_
