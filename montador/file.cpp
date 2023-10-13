#include <iostream>
#include <fstream>
#include "file.h"

std::string get_filename(const std::string& path)
{
	std::string filename;

	auto dotIndex = path.find('.');

	if (dotIndex != std::string::npos)
	{
		filename = path.substr(0, dotIndex);
	}
	else
	{
		std::cerr << "CAMINHO INVALIDO" << std::endl;
		abort();
	}
	return filename;
}

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

void write_file(const std::string& filename, const std::vector<int>& objectCode)
{
	std::string line;
	std::ofstream file(filename + ".obj");

	if (file.fail())
	{
		std::cerr << "NAO FOI POSSIVEL CRIAR O ARQUIVO OBJETO" << std::endl;
		abort();
	}
	for (int value : objectCode)
	{
		file << value << ' ';
	}
	file.close();
}
