#include <iostream>
#include "file.h"

using namespace std;

int main(int argc, char* argv[])
{
	string path;
	vector<string> instructions;

	if (argc < 2)
	{
		cerr << "CAMINHO NAO FORNECIDO" << endl;
		exit(1);
	}
	path = argv[1];
	instructions = read_file(path);

	return 0;
}
