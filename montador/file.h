#include <vector>
#include <string>

#ifndef TRABALHO1_SB_MONTADOR_FILE_H_
#define TRABALHO1_SB_MONTADOR_FILE_H_

std::string get_filename(const std::string& path);
std::vector<std::string> read_file(const std::string& path);
void write_file(const std::string& fileName, const std::vector<int>& objectCode);

#endif //TRABALHO1_SB_MONTADOR_FILE_H_
