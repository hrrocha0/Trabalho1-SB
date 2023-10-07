#include "SymbolTable.h"

void SymbolTable::add(const std::string& label, int address)
{
	this->entries[label] = address;
}

bool SymbolTable::find(const std::string& label)
{
	return this->entries.count(label);
}

int SymbolTable::getAddress(const std::string& label)
{
	return this->entries[label];
}
