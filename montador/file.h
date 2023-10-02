#ifndef TRABALHO1_SB_MONTADOR_FILE_H_
#define TRABALHO1_SB_MONTADOR_FILE_H_

#include <vector>
#include <string>

/**
 * Lê um arquivo e armazena as linhas em um vetor.
 * @param path - o caminho do arquivo.
 * @return o vetor contendo as linhas lidas do arquivo.
 */
std::vector<std::string> read_file(const std::string& path);

#endif //TRABALHO1_SB_MONTADOR_FILE_H_
