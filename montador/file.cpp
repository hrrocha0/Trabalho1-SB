#include "file.h"
#include <iostream>
#include <fstream>

using namespace std;

vector<string> read_file(const string& path)
{
	vector<string> lines;
	string line;
	ifstream file(path);

	if (file.fail())
	{
		cerr << "ARQUIVO NAO ENCONTRADO" << endl;
		exit(1);
	}
	while (getline(file, line))
	{
		lines.push_back(line);
	}
	file.close();

	return lines;
}
