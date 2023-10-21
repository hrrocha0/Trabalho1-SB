#include "Macro.h"

const std::string& Macro::GetName()
{
	return this->name;
}

const std::string& Macro::GetParameter(int index)
{
	return this->parameters[index];
}

const std::string& Macro::GetLine(int index)
{
	return this->code[index];
}

const std::vector<std::string>& Macro::GetParameters()
{
	return this->parameters;
}

const std::vector<std::string>& Macro::GetCode()
{
	return this->code;
}

int Macro::GetParameterCount()
{
	return (int)this->parameters.size();
}

void Macro::SetName(const std::string& _name)
{
	this->name = _name;
}

void Macro::SetParameter(int index, const std::string& parameter)
{
	this->parameters[index] = parameter;
}

void Macro::SetLine(int index, const std::string& line)
{
	this->code[index] = line;
}

void Macro::SetParameters(const std::vector<std::string>& _parameters)
{
	this->parameters = _parameters;
}

void Macro::SetCode(const std::vector<std::string>& _code)
{
	this->code = _code;
}

void Macro::AddParameter(const std::string& parameter)
{
	this->parameters.push_back(parameter);
}

void Macro::AddLine(const std::string& line)
{
	this->code.push_back(line);
}
