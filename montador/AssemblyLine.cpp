#include <sstream>
#include "AssemblyLine.h"

std::string uppercase(const std::string& s)
{
	std::string result;

	for (char c : s)
	{
		result.push_back((char)toupper(c));
	}
	return result;
}

std::string replace_tabs_with_spaces(const std::string& s)
{
	std::string result = s;

	for (char& c : result)
	{
		if (c == '\t')
		{
			c = ' ';
		}
	}
	return result;
}

AssemblyLine::AssemblyLine(const std::string& line)
{
	std::istringstream stream(replace_tabs_with_spaces(line));
	std::string token;

	while (std::getline(stream, token, ' '))
	{
		if (token.empty())
			continue;
		if (token.front() == ';')
			break;
		if (token.back() == ':')
		{
			token.pop_back();
			this->label = uppercase(token);
		}
		else if (this->operation.empty())
		{
			this->operation = uppercase(token);
		}
		else
		{
			this->operands.push_back(uppercase(token));
		}
	}
}

std::string AssemblyLine::getLabel()
{
	return this->label;
}

std::string AssemblyLine::getOperation()
{
	return this->operation;
}

std::string AssemblyLine::getOperand(int index)
{
	return this->operands[index];
}

std::vector<std::string> AssemblyLine::getOperands()
{
	return this->operands;
}

std::size_t AssemblyLine::getSize()
{
	return this->operands.size() + 1;
}
