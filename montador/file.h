#include <vector>
#include <string>

#ifndef TRABALHO1_SB_MONTADOR_FILE_H_
#define TRABALHO1_SB_MONTADOR_FILE_H_

/**
 * Obtém o nome do arquivo a partir de seu caminho, retirando-se a extensão.
 * @param path - o caminho do arquivo.
 * @return o caminho do arquivo sem a extensão.
 */
std::string get_filename(const std::string& path);

/**
 * Lê um arquivo e armazena as suas linhas em um vetor.
 * @param path - o caminho do arquivo.
 * @return um vetor com as linhas do arquivo.
 */
std::vector<std::string> read_file(const std::string& path);

/**
 * Escreve o código objeto gerado pela passagem 0 em um arquivo, com a extensão ".pre".
 * @param filename - o caminho do arquivo sem a extensão.
 * @param preProcessedCode - o código pré-processado que será escrito no arquivo.
 */
void write_pre_processed_file(const std::string& filename, const std::vector<std::string>& preProcessedCode);

/**
 * Escreve o código objeto gerado pela segunda passagem em um arquivo, com a extensão ".obj".
 * @param filename - o caminho do arquivo sem a extensão.
 * @param objectCode - o código objeto que será escrito no arquivo.
 */
void write_object_file(const std::string& filename, const std::vector<int>& objectCode);


#endif //TRABALHO1_SB_MONTADOR_FILE_H_
