#include "InstructionTable.h"

void InstructionTable::add(const std::string& operation, int opcode, int size)
{
	this->entries[operation] = { opcode, size };
}

bool InstructionTable::find(const std::string& operation)
{
	return this->entries.count(operation);
}

int InstructionTable::getOpcode(const std::string& operation)
{
	return this->entries[operation].first;
}

int InstructionTable::getSize(const std::string& operation)
{
	return this->entries[operation].second;
}
