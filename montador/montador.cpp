#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>
#include "InstructionTable.h"
#include "SymbolTable.h"
#include "MacroTable.h"
#include "AssemblyLine.h"
#include "Macro.h"

/**
 * Obtém o nome do arquivo a partir de seu caminho, retirando-se a extensão.
 * @param filePath - o caminho do arquivo.
 * @return o caminho do arquivo sem a extensão.
 */
std::string get_filename(const std::string& filePath);

/**
 * Obtém a extensão do arquivo a partir de seu caminho.
 * @param filePath - o caminho do arquivo.
 * @return a extensão do arquivo.
 */
std::string get_extension(const std::string& filePath);

/**
 * Lê um arquivo e armazena as suas linhas em um vetor.
 * @param filePath - o caminho do arquivo.
 * @return um vetor com as linhas do arquivo.
 */
std::vector<std::string> read_file(const std::string& filePath);

/**
 * Escreve o código pré-processado gerado pela passagem zero em um arquivo, com a extensão ".pre".
 * @param fileName - o caminho do arquivo sem a extensão.
 * @param preCode - o código pré-processado que será escrito no arquivo.
 */
void write_pre(const std::string& fileName, const std::vector<std::string>& preCode);

/**
 * Escreve o código objeto gerado pela segunda passagem em um arquivo, com a extensão ".obj".
 * @param fileName - o caminho do arquivo sem a extensão.
 * @param objCode - o código objeto que será escrito no arquivo.
 */
void write_obj(const std::string& fileName, const std::vector<int>& objCode);

/**
 * Realiza a passagem zero do montador. Gera o código pré-processado, sem as macros,
 * a partir do código fonte, e armazena as suas linhas em um vetor.
 * @param lines - as linhas do código fonte.
 * @param preCode - ume referência ao vetor que armazena o código pré-processado.
 * @return true, se não houveram erros, false, caso contrário.
 */
bool zero_pass(const std::vector<std::string>& lines,
	std::vector<std::string>& preCode,
	MacroTable& macroTable);

/**
 * Executa a primeira passagem do algoritmo de duas passagens do montador. Armazena os rótulos
 * e seus respectivos endereços na tabela de símbolos.
 * @param lines - as linhas do código fonte.
 * @param symbolTable - uma referência à tabela de símbolos.
 * @param instructionTable - a tabela de instruções.
 * @return true, se não houveram erros, false, caso contrário.
 */
bool first_pass(
	const std::vector<std::string>& lines,
	SymbolTable& symbolTable,
	InstructionTable instructionTable
);

/**
 * Executa a segunda passagem do algoritmo de duas passagens do montador. Utiliza a tabela de
 * símbolos gerada pela primeira passagem para gerar o código objeto, que será armazenado em um
 * vetor.
 * @param lines - as linhas do código fonte.
 * @param objCode - uma referência ao vetor que armazena o código objeto.
 * @param symbolTable - a tabela de símbolos.
 * @param instructionTable - a tabela de instruções.
 * @return true, se não houveram erros, false, caso contrário.
 */
bool second_pass(
	const std::vector<std::string>& lines,
	std::vector<int>& objCode,
	SymbolTable symbolTable,
	InstructionTable instructionTable
);

/*
 * Software Básico (2023.2) - Trabalho 1
 * Henrique Rodrigues Rocha: 211036061
 * Vinícius de Sousa Brito: 211042748
 */
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "CAMINHO NAO FORNECIDO" << std::endl;
		std::cerr << "Uso correto: " << argv[0] << " <arquivo.asm>" << std::endl;

		return 1;
	}
	std::string filePath = argv[1];
	std::string fileName = get_filename(filePath);
	std::string fileExtension = get_extension(filePath);

	std::vector<std::string> lines = read_file(filePath);
	std::vector<std::string> preCode;
	std::vector<int> objCode;

	SymbolTable symbolTable;
	InstructionTable instructionTable;
	MacroTable macroTable;

	instructionTable.add("ADD", 1, 2);
	instructionTable.add("SUB", 2, 2);
	instructionTable.add("MUL", 3, 2);
	instructionTable.add("DIV", 4, 2);
	instructionTable.add("JMP", 5, 2);
	instructionTable.add("JMPN", 6, 2);
	instructionTable.add("JMPP", 7, 2);
	instructionTable.add("JMPZ", 8, 2);
	instructionTable.add("COPY", 9, 3);
	instructionTable.add("LOAD", 10, 2);
	instructionTable.add("STORE", 11, 2);
	instructionTable.add("INPUT", 12, 2);
	instructionTable.add("OUTPUT", 13, 2);
	instructionTable.add("STOP", 14, 1);

	bool generatePre = false;
	bool generateObj = true;

	if (fileExtension == ".mcr")
	{
		generatePre = zero_pass(lines, preCode, macroTable);
		lines = preCode;
	}
	generateObj &= first_pass(lines, symbolTable, instructionTable);
	generateObj &= second_pass(lines, objCode, symbolTable, instructionTable);

	if (generatePre)
	{
		write_pre(fileName, preCode);
	}
	if (generateObj)
	{
		write_obj(fileName, objCode);
	}
	return 0;
}

std::string get_filename(const std::string& filePath)
{
	std::string filename;
	std::size_t dotIndex = filePath.find('.');

	if (dotIndex == std::string::npos)
	{
		std::cerr << "CAMINHO INVALIDO" << std::endl;
		abort();
	}
	filename = filePath.substr(0, dotIndex);

	return filename;
}

std::string get_extension(const std::string& filePath)
{
	std::string extension;
	std::size_t dotIndex = filePath.find('.');

	if (dotIndex == std::string::npos)
	{
		std::cerr << "CAMINHO INVALIDO" << std::endl;
		abort();
	}
	extension = filePath.substr(dotIndex);

	return extension;
}

std::vector<std::string> read_file(const std::string& filePath)
{
	std::ifstream file(filePath);
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

void write_obj(const std::string& fileName, const std::vector<int>& objCode)
{
	std::ofstream file(fileName + ".obj");

	if (file.fail())
	{
		std::cerr << "NAO FOI POSSIVEL CRIAR O ARQUIVO OBJETO" << std::endl;
		abort();
	}
	for (int value : objCode)
	{
		file << value << ' ';
	}
	file.close();
	std::cout << "ARQUIVO .obj GERADO" << std::endl;
}

void write_pre(const std::string& fileName, const std::vector<std::string>& preCode)
{
	std::ofstream file(fileName + ".pre");

	if (file.fail())
	{
		std::cerr << "NAO FOI POSSIVEL CRIAR O ARQUIVO PRE-PROCESSADO (SEM AS MACROS)" << std::endl;
		abort();
	}
	for (const auto& value : preCode)
	{
		file << value << '\n';
	}
	file.close();
	std::cout << "ARQUIVO .pre GERADO" << std::endl;
}

/**
 * Imprime no console uma mensagem de erro léxico.
 * @param line - a linha onde está o erro.
 * @param lineCounter - o número da linha.
 */
void lexical_error(const std::string& line, int lineCounter)
{
	std::cerr << "ERRO LEXICO:\t\t" << lineCounter << ". " << line << std::endl;
}

/**
 * Imprime no console uma mensagem de erro sintático.
 * @param line - a linha onde está o erro.
 * @param lineCounter - o número da linha.
 */
void syntatical_error(const std::string& line, int lineCounter)
{
	std::cerr << "ERRO SINTATICO:\t\t" << lineCounter << ". " << line << std::endl;
}

/**
 * Imprime no console uma mensagem de erro semântico.
 * @param line - a linha onde está o erro.
 * @param lineCounter - o número da linha.
 */
void semantical_error(const std::string& line, int lineCounter)
{
	std::cerr << "ERRO SEMANTICO:\t\t" << lineCounter << ". " << line << std::endl;
}

/**
 * Divide uma linha em tokens, separados por espaço.
 * @param line - a linha que será dividida.
 * @return um vetor contendo os tokens.
 */
std::vector<std::string> tokenize(const std::string& line)
{
	std::istringstream stream(line);
	std::vector<std::string> tokens;
	std::string token;

	while (stream >> token)
	{
		tokens.push_back(token);
	}
	return tokens;
}

/**
 * Expande uma macro, substituindo as chamadas de macro pelo código da macro.
 * @param macro - a macro que foi chamada.
 * @param arguments - os argumentos da chamada de macro.
 * @param macroTable - a tabela de macros.
 * @return um vetor com o código gerado pela expansão da macro.
 */
std::vector<std::string> expand_macro(Macro macro,
	MacroTable macroTable,
	std::vector<std::string>& arguments)
{
	std::vector<std::string> expandedCode;

	for (const auto& source : macro.GetCode())
	{
		AssemblyLine line(source);
		std::vector<std::string> tokens = tokenize(source);

		for (auto& token : tokens)
		{
			for (int j = 0; j < macro.GetParameterCount(); j++)
			{
				std::size_t pos = 0;

				while (true)
				{
					std::string t = macro.GetParameter(j);

					pos = token.find(macro.GetParameter(j), pos);

					if (pos == std::string::npos)
						break;

					token.erase(pos, macro.GetParameter(j).length());
					token.insert(pos, arguments[j]);
					pos += arguments[j].size();
				}
			}
		}
		if (macroTable.Find(line.getOperation()))
		{
			Macro innerMacro = macroTable.GetMacro(line.getOperation());
			std::vector<std::string> innerArguments = line.getOperands();
			std::vector<std::string>
				innerExpanded = expand_macro(innerMacro, macroTable, innerArguments);

			for (const auto& innerSource : innerExpanded)
			{
				std::vector<std::string> innerTokens = tokenize(innerSource);
				std::string innerJoined;

				for (auto& token : innerTokens)
				{
					for (int j = 0; j < innerMacro.GetParameterCount(); j++)
					{
						std::size_t pos = 0;

						while (true)
						{
							std::string t = innerMacro.GetParameter(j);

							pos = token.find(innerMacro.GetParameter(j), pos);

							if (pos == std::string::npos)
								break;

							token.erase(pos, innerMacro.GetParameter(j).length());
							token.insert(pos, arguments[j]);
							pos += arguments[j].size();
						}
					}
				}
				for (const auto& token : innerTokens)
				{
					innerJoined += token + ' ';
				}
				expandedCode.push_back(innerJoined);
			}
		}
		else
		{
			std::string joinedLine;

			for (const auto& token : tokens)
			{
				joinedLine += token + " ";
			}
			expandedCode.push_back(joinedLine);
		}
	}
	return expandedCode;
}

bool zero_pass(const std::vector<std::string>& lines,
	std::vector<std::string>& preCode,
	MacroTable& macroTable)
{
	std::string name;
	Macro macro;

	bool inMacroDefinition = false;

	for (const std::string& source : lines)
	{
		if (source.empty())
			continue;

		AssemblyLine line(source);

		if (line.getOperation() == "MACRO")
		{
			inMacroDefinition = true;

			name = line.getLabel();

			macro.SetName(name);
			macro.SetParameters({});
			macro.SetCode({});

			std::vector<std::string> parameters = line.getOperands();

			for (const auto& parameter : parameters)
			{
				macro.AddParameter(parameter);
			}
		}
		else if (inMacroDefinition)
		{
			if (line.getOperation() != "ENDMACRO")
			{
				macro.AddLine(source);
				continue;
			}
			std::string label = line.getLabel();

			inMacroDefinition = false;
			macroTable.Add(name, macro);
		}
		else
		{
			if (!macroTable.Find(line.getOperation()))
			{
				preCode.push_back(source);
				continue;
			}
			std::string calledName = line.getOperation();
			std::vector<std::string> parameters = line.getOperands();

			Macro calledMacro = macroTable.GetMacro(calledName);
			MacroTable table = macroTable;

			std::vector<std::string>
				expandedCode = expand_macro(calledMacro, table, parameters);

			if (!line.getLabel().empty())
			{
				expandedCode[0] = line.getLabel() + ": " + expandedCode[0];
			}
			preCode.insert(preCode.end(), expandedCode.begin(), expandedCode.end());
		}
	}
	return true;
}

bool first_pass(const std::vector<std::string>& lines,
	SymbolTable& symbolTable,
	InstructionTable instructionTable)
{
	std::map<std::string, int> textSection, dataSection;
	std::string currentSection;

	std::regex labelRegex(R"([A-Z_][A-Z0-9_]{0,29})");
	std::regex spaceRegex(R"([0-9]+)");

	int locationCounter = 0;
	int lineCounter = 1;
	int textAddress = 0;
	int dataAddress = 0;

	bool generateFile = true;

	for (const auto& source : lines)
	{
		AssemblyLine line(source);

		if (!line.getLabel().empty())
		{
			auto label = line.getLabel();

			if (regex_match(label, labelRegex))
			{
				if (currentSection == "TEXT")
				{
					if (!textSection.count(label))
					{
						textSection[label] = locationCounter;
					}
					else
					{
						semantical_error(source, lineCounter);
						generateFile = false;
					}
				}
				else if (currentSection == "DATA")
				{
					if (!dataSection.count(label))
					{
						dataSection[label] = locationCounter;
					}
					else
					{
						semantical_error(source, lineCounter);
						generateFile = false;
					}
				}
			}
			else
			{
				lexical_error(source, lineCounter);
				generateFile = false;
			}
		}
		if (line.getOperation().empty())
		{
			lineCounter++;
			continue;
		}
		auto operation = line.getOperation();

		if (instructionTable.find(operation))
		{
			locationCounter += instructionTable.getSize(operation);
		}
		else if (operation == "SECAO")
		{
			if (line.getSize() == 2)
			{
				auto section = line.getOperand(0);

				if (section == "TEXT")
				{
					currentSection = section;
					locationCounter = textAddress;
				}
				else if (section == "DATA")
				{
					currentSection = section;
					locationCounter = dataAddress;
				}
				else
				{
					syntatical_error(source, lineCounter);
					generateFile = false;
				}
			}
			else
			{
				syntatical_error(source, lineCounter);
				generateFile = false;
			}
		}
		else if (operation == "SPACE")
		{
			if (line.getSize() == 2)
			{
				if (regex_match(line.getOperand(0), spaceRegex))
				{
					locationCounter += std::stoi(line.getOperand(0));
				}
				else
				{
					lexical_error(source, lineCounter);
					generateFile = false;
				}
			}
			else if (line.getSize() == 1)
			{
				locationCounter++;
			}
			else
			{
				syntatical_error(source, lineCounter);
				generateFile = false;
			}
		}
		else if (operation == "CONST")
		{
			locationCounter++;
		}
		else
		{
			syntatical_error(source, lineCounter);
			generateFile = false;
		}
		if (currentSection == "TEXT")
		{
			textAddress = locationCounter;
		}
		else if (currentSection == "DATA")
		{
			dataAddress = locationCounter;
		}
		else if (!line.getLabel().empty() || !line.getOperation().empty())
		{
			semantical_error(source, lineCounter);
			generateFile = false;
		}
		lineCounter++;
	}
	for (const auto& entry : textSection)
	{
		symbolTable.add(entry.first, entry.second);
	}
	for (const auto& entry : dataSection)
	{
		symbolTable.add(entry.first, entry.second + textAddress);
	}
	return generateFile;
}

bool second_pass(
	const std::vector<std::string>& lines,
	std::vector<int>& objCode,
	SymbolTable symbolTable,
	InstructionTable instructionTable
)
{
	std::vector<int> textSection, dataSection;
	std::string currentSection;

	std::regex addressRegex(R"([A-Z_][A-Z0-9_]{0,29}(\+[0-9]+)?)");
	std::regex constRegex(R"(\-?[0-9]+)");

	int lineCounter = 1;

	bool generateFile = true;

	for (const auto& source : lines)
	{
		AssemblyLine line(source);

		if (line.getOperation().empty())
		{
			lineCounter++;
			continue;
		}
		auto operation = line.getOperation();

		if (instructionTable.find(operation))
		{
			int opcode = instructionTable.getOpcode(operation);

			if (currentSection == "TEXT")
			{
				textSection.push_back(opcode);

				if (line.getSize() == instructionTable.getSize(operation))
				{
					for (const auto& operand : line.getOperands())
					{
						if (!regex_match(operand, addressRegex))
						{
							lexical_error(source, lineCounter);
							generateFile = false;
							lineCounter++;

							break;
						}
						std::string label;
						auto plusIndex = operand.find('+');
						int offset;

						if (plusIndex != std::string::npos)
						{
							label = operand.substr(0, plusIndex);
							offset = stoi(operand.substr(plusIndex + 1));
						}
						else
						{
							label = operand;
							offset = 0;
						}
						if (!symbolTable.find(label))
						{
							semantical_error(source, lineCounter);
							generateFile = false;
							lineCounter++;

							break;
						}
						textSection.push_back(symbolTable.getAddress(label) + offset);
					}
				}
				else
				{
					syntatical_error(source, lineCounter);
					generateFile = false;
					lineCounter++;
				}
			}
			else if (currentSection == "DATA")
			{
				dataSection.push_back(opcode);

				for (const auto& operand : line.getOperands())
				{
					dataSection.push_back(symbolTable.getAddress(operand));
				}
			}
		}
		else if (operation == "SECAO")
		{
			if (line.getSize() == 2)
			{
				auto section = line.getOperand(0);

				if (section == "TEXT" || section == "DATA")
				{
					currentSection = section;
				}
			}
		}
		else if (operation == "SPACE")
		{
			if (line.getSize() == 2)
			{
				int value = stoi(line.getOperand(0));

				for (int i = 0; i < value; i++)
				{
					if (currentSection == "TEXT")
					{
						textSection.push_back(0);
					}
					else if (currentSection == "DATA")
					{
						dataSection.push_back(0);
					}
				}
			}
			else if (line.getSize() == 1)
			{
				if (currentSection == "TEXT")
				{
					textSection.push_back(0);
				}
				else if (currentSection == "DATA")
				{
					dataSection.push_back(0);
				}
			}
		}
		else if (operation == "CONST")
		{
			if (line.getSize() == 2)
			{
				if (regex_match(line.getOperand(0), constRegex))
				{
					int value = stoi(line.getOperand(0));

					if (currentSection == "TEXT")
					{
						textSection.push_back(value);
					}
					else if (currentSection == "DATA")
					{
						dataSection.push_back(value);
					}
				}
				else
				{
					lexical_error(source, lineCounter);
					generateFile = false;
				}
			}
			else
			{
				syntatical_error(source, lineCounter);
				generateFile = false;
			}
		}
		lineCounter++;
	}
	for (int value : textSection)
	{
		objCode.push_back(value);
	}
	for (int value : dataSection)
	{
		objCode.push_back(value);
	}
	return generateFile;
}
