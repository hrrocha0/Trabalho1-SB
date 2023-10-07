#include <iostream>
#include <fstream>
#include "file.h"

std::vector<std::string> read_file(const std::string& path)
{
	std::ifstream file(path);
	std::vector<std::string> lines;
	std::string line;

	if (file.fail())
	{
		std::cerr << "ARQUIVO NAO ENCONTRADO" << std::endl;
		abort();
	}
	while (std::getline(file, line))
	{
		lines.push_back(line);
	}
	file.close();

	return lines;
}
