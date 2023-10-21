#include <map>
#include <string>
#include "Macro.h"

#ifndef TRABALHO1_SB_MONTADOR_MACROTABLE_H_
#define TRABALHO1_SB_MONTADOR_MACROTABLE_H_

class MacroTable
{
 public:
	void Add(const std::string& name, const Macro& macro);

	bool Find(const std::string& name);
	Macro GetMacro(const std::string& name);
 private:
	std::map<std::string, Macro> entries;
};

#endif //TRABALHO1_SB_MONTADOR_MACROTABLE_H_
