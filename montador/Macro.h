#include <vector>
#include <string>

#ifndef TRABALHO1_SB_MONTADOR_MACRO_H_
#define TRABALHO1_SB_MONTADOR_MACRO_H_

class Macro
{
 public:
	const std::string& GetName();
	const std::string& GetParameter(int index);
	const std::string& GetLine(int index);
	const std::vector<std::string>& GetParameters();
	const std::vector<std::string>& GetCode();
	int GetParameterCount();

	void SetName(const std::string& _name);
	void SetParameter(int index, const std::string& parameter);
	void SetLine(int index, const std::string& line);
	void SetParameters(const std::vector<std::string>& _parameters);
	void SetCode(const std::vector<std::string>& _code);

	void AddParameter(const std::string& parameter);
	void AddLine(const std::string& line);
 private:
	std::string name;
	std::vector<std::string> parameters;
	std::vector<std::string> code;
};

#endif //TRABALHO1_SB_MONTADOR_MACRO_H_
