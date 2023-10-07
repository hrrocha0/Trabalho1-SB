#include <map>
#include <string>

#ifndef TRABALHO1_SB_MONTADOR_SYMBOLTABLE_H_
#define TRABALHO1_SB_MONTADOR_SYMBOLTABLE_H_

class SymbolTable
{
 public:
	void add(const std::string& label, int address);

	bool find(const std::string& label);
	int getAddress(const std::string& label);
 private:
	std::map<std::string, int> entries;
};

#endif //TRABALHO1_SB_MONTADOR_SYMBOLTABLE_H_
