#include <map>
#include <string>

#ifndef TRABALHO1_SB_MONTADOR_INSTRUCTIONTABLE_H_
#define TRABALHO1_SB_MONTADOR_INSTRUCTIONTABLE_H_

class InstructionTable
{
 public:
	void add(const std::string& operation, int opcode, int size);

	bool find(const std::string& operation);
	int getOpcode(const std::string& operation);
	int getSize(const std::string& operation);
 private:
	std::map<std::string, std::pair<int, int>> entries;
};

#endif //TRABALHO1_SB_MONTADOR_INSTRUCTIONTABLE_H_
