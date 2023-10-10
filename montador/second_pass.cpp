#include <regex>
#include "error.h"
#include "second_pass.h"
#include "AssemblyLine.h"

bool second_pass(
	const std::vector<std::string>& lines,
	std::vector<int>& objectCode,
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

	for (const auto& l : lines)
	{
		AssemblyLine line(l);

		if (!line.getOperation().empty())
		{
			auto operation = line.getOperation();

			if (instructionTable.find(operation))
			{
				int opcode = instructionTable.getOpcode(operation);

				if (currentSection == "TEXT")
				{
					textSection.push_back(opcode);

					for (const auto& operand : line.getOperands())
					{
						if (regex_match(operand, addressRegex))
						{
							std::string label;
							int offset;
							auto plusIndex = operand.find('+');

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
							if (symbolTable.find(label))
							{
								textSection.push_back(symbolTable.getAddress(label) + offset);
							}
							else
							{
								semanticalError(l, lineCounter);
								generateFile = false;
								lineCounter++;

								break;
							}
						}
						else
						{
							lexicalError(l, lineCounter);
							generateFile = false;
							lineCounter++;

							break;
						}
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
						lexicalError(l, lineCounter);
						generateFile = false;
					}
				}
				else
				{
					syntaticalError(l, lineCounter);
					generateFile = false;
				}
			}
		}
		lineCounter++;
	}
	for (int value : textSection)
	{
		objectCode.push_back(value);
	}
	for (int value : dataSection)
	{
		objectCode.push_back(value);
	}
	return generateFile;
}
