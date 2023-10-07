#include <vector>
#include <string>

#ifndef TRABALHO1_SB_MONTADOR_ASSEMBLYLINE_H_
#define TRABALHO1_SB_MONTADOR_ASSEMBLYLINE_H_

class AssemblyLine
{
 public:
	explicit AssemblyLine(const std::string& line);

	std::string getLabel();
	std::string getOperation();
	std::string getOperand(int index);
	std::vector<std::string> getOperands();
	std::size_t getSize();
 private:
	std::string label, operation;
	std::vector<std::string> operands;
};

#endif //TRABALHO1_SB_MONTADOR_ASSEMBLYLINE_H_
