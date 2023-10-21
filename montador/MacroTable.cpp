#include "MacroTable.h"

void MacroTable::Add(const std::string& name, const Macro& macro)
{
	this->entries[name] = macro;
}

bool MacroTable::Find(const std::string& name)
{
	return this->entries.count(name);
}

Macro MacroTable::GetMacro(const std::string& name)
{
	return this->entries[name];
}
