#include <iostream>
#include <map>
#include <regex>
#include "first_pass.h"
#include "AssemblyLine.h"

void first_pass(const std::vector<std::string>& lines,
	SymbolTable& symbolTable,
	InstructionTable instructionTable)
{
	std::map<std::string, int> textSection, dataSection;
	std::string currentSection;
	std::regex labelRegex(R"([A-Z_][A-Z0-9_]{0,29})"), spaceRegex(R"([0-9]+)"),
		constRegex(R"(\-?[0-9]+)");
	int locationCounter = 0, lineCounter = 1, textAddress = 0, dataAddress = 0;

	for (const auto& l : lines)
	{
		AssemblyLine line(l);

		if (!line.getLabel().empty())
		{
			auto label = line.getLabel();

			if (regex_match(label, labelRegex))
			{
				if (!symbolTable.find(label))
				{
					if (currentSection == "TEXT")
					{
						if (!textSection.count(label))
						{
							textSection[label] = locationCounter;
						}
						else
						{
							std::cerr << "ERRO SEMANTICO:\t\t" << lineCounter << ". " << l
									  << std::endl;
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
							std::cerr << "ERRO SEMANTICO:\t\t" << lineCounter << ". " << l
									  << std::endl;
						}
					}
				}
			}
			else
			{
				std::cerr << "ERRO LEXICO:\t\t" << lineCounter << ". " << l << std::endl;
			}
		}
		if (!line.getOperation().empty())
		{
			auto operation = line.getOperation();

			if (instructionTable.find(operation))
			{
				int size = instructionTable.getSize(operation);
				locationCounter += size;
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
						std::cerr << "ERRO SINTATICO:\t\t" << lineCounter << ". " << l << std::endl;
					}
				}
				else
				{
					std::cerr << "ERRO SINTATICO:\t\t" << lineCounter << ". " << l << std::endl;
				}
			}
			else if (operation == "SPACE")
			{
				if (line.getSize() == 2)
				{
					if (regex_match(line.getOperand(0), spaceRegex))
					{
						int size = std::stoi(line.getOperand(0));
						locationCounter += size;
					}
					else
					{
						std::cerr << "ERRO LEXICO:\t\t" << lineCounter << ". " << l << std::endl;
					}
				}
				else if (line.getSize() == 1)
				{
					locationCounter++;
				}
				else
				{
					std::cerr << "ERRO SINTATICO:\t\t" << lineCounter << ". " << l << std::endl;
				}
			}
			else if (operation == "CONST")
			{
				if (line.getSize() == 2)
				{
					if (regex_match(line.getOperand(0), constRegex))
					{
						locationCounter++;
					}
					else
					{
						std::cerr << "ERRO LEXICO:\t\t" << lineCounter << ". " << l << std::endl;
					}
				}
				else
				{
					std::cerr << "ERRO SINTATICO:\t\t" << lineCounter << ". " << l << std::endl;
				}
			}
			else
			{
				std::cerr << "ERRO SINTATICO:\t\t" << lineCounter << ". " << l << std::endl;
			}
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
			std::cerr << "ERRO SEMANTICO:\t\t" << lineCounter << ". " << l << std::endl;
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
}
