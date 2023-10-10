#include <iostream>
#include "error.h"

void lexicalError(const std::string& line, int lineCounter)
{
	std::cerr << "ERRO LEXICO:\t\t" << lineCounter << ". " << line << std::endl;
}

void syntaticalError(const std::string& line, int lineCounter)
{
	std::cerr << "ERRO SINTATICO:\t\t" << lineCounter << ". " << line << std::endl;
}

void semanticalError(const std::string& line, int lineCounter)
{
	std::cerr << "ERRO SEMANTICO:\t\t" << lineCounter << ". " << line << std::endl;
}
