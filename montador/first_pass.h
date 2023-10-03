#ifndef TRABALHO1_SB_MONTADOR_FIRST_PASS_H_
#define TRABALHO1_SB_MONTADOR_FIRST_PASS_H_

#include <vector>
#include <map>
#include <string>

void first_pass(
	const std::vector<std::string>& lines,
	const std::map<std::string, std::pair<int, int>>& instructionTable,
	const std::map<std::string, int>& directiveTable,
	std::map<std::string, int>& symbolTable
);

#endif //TRABALHO1_SB_MONTADOR_FIRST_PASS_H_
