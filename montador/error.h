#ifndef TRABALHO1_SB_MONTADOR_ERROR_H_
#define TRABALHO1_SB_MONTADOR_ERROR_H_

/**
 * Imprime no console uma mensagem de erro léxico.
 * @param line - a linha onde está o erro.
 * @param lineCounter - o número da linha.
 */
void lexicalError(const std::string& line, int lineCounter);

/**
 * Imprime no console uma mensagem de erro sintático.
 * @param line - a linha onde está o erro.
 * @param lineCounter - o número da linha.
 */
void syntaticalError(const std::string& line, int lineCounter);

/**
 * Imprime no console uma mensagem de erro semântico.
 * @param line - a linha onde está o erro.
 * @param lineCounter - o número da linha.
 */
void semanticalError(const std::string& line, int lineCounter);

#endif //TRABALHO1_SB_MONTADOR_ERROR_H_
