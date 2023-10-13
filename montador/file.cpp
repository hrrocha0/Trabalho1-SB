#include <iostream>
#include <fstream>
#include "file.h"

std::string get_filename(const std::string& path)
{
	std::string filename;
	std::size_t dotIndex = path.find('.');

	if (dotIndex == std::string::npos)
	{
		std::cerr << "CAMINHO INVALIDO" << std::endl;
		abort();
	}
	filename = path.substr(0, dotIndex);

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
	std::ofstream file(filename + ".obj");
	std::string line;

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
