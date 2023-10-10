#include <map>
#include <regex>
#include "error.h"
#include "first_pass.h"
#include "AssemblyLine.h"

bool first_pass(const std::vector<std::string>& lines,
	SymbolTable& symbolTable,
	InstructionTable instructionTable)
{
	std::map<std::string, int> textSection, dataSection;
	std::string currentSection;

	std::regex labelRegex(R"([A-Z_][A-Z0-9_]{0,29})");
	std::regex spaceRegex(R"([0-9]+)");

	int locationCounter = 0, lineCounter = 1, textAddress = 0, dataAddress = 0;
	bool generateFile = true;

	for (const auto& l : lines)
	{
		AssemblyLine line(l);

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
						semanticalError(l, lineCounter);
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
						semanticalError(l, lineCounter);
						generateFile = false;
					}
				}
			}
			else
			{
				lexicalError(l, lineCounter);
				generateFile = false;
			}
		}
		if (!line.getOperation().empty())
		{
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
						syntaticalError(l, lineCounter);
						generateFile = false;
					}
				}
				else
				{
					syntaticalError(l, lineCounter);
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
						lexicalError(l, lineCounter);
						generateFile = false;
					}
				}
				else if (line.getSize() == 1)
				{
					locationCounter++;
				}
				else
				{
					syntaticalError(l, lineCounter);
					generateFile = false;
				}
			}
			else if (operation == "CONST")
			{
				locationCounter++;
			}
			else
			{
				syntaticalError(l, lineCounter);
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
				semanticalError(l, lineCounter);
				generateFile = false;
			}
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
