#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include "AssemblyLine.h"

using namespace std;

// Estrutura para representar uma macro
struct Macro {
    string name;
    vector<string> parameters;
    vector<string> code;
};

// Função para dividir uma linha em tokens
vector<string> tokenize(const string& line) {
    vector<string> tokens;
    istringstream iss(line);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Função para expandir uma macro (substituir chamadas de macro pelo codigo da macro)
vector<string> expandMacro(const Macro& macro, vector<string>& arguments, const map<string, Macro>& macroTable) {
    vector<string> expandedCode;

    for (const string& line : macro.code) {

        for (std::string& str : arguments) {
            str.erase(std::remove(str.begin(), str.end(), '&'), str.end());
        }


        AssemblyLine l(line);

        vector<string> tokens = tokenize(line);

        // Substituir argumentos pelos valores passados
        for (size_t i = 0; i < tokens.size(); i++) {
            for (size_t j = 0; j < macro.parameters.size(); j++) {
                if (tokens[i] == macro.parameters[j]) {
                    tokens[i] = arguments[j];
                }
            }
        }

        // Verificar se a linha contém uma chamada de macro (para casos de chamada de macro dentro de outra macro)
        if (macroTable.find(l.getOperation()) != macroTable.end()) {
            // Chamar a função para expandir a macro interna
            vector<string> innerArguments(l.getOperands());
            vector<string> innerExpanded = expandMacro(macroTable.at(l.getOperation()), innerArguments, macroTable);
            if (!l.getLabel().empty()){
                innerExpanded.insert(innerExpanded.begin(), l.getLabel() + ":");
            }

            expandedCode.insert(expandedCode.end(), innerExpanded.begin(), innerExpanded.end());
        } else {
            // Se não for uma chamada de macro, adicionar a linha ao código expandido
            string joinedLine = "";
            for (const string& token : tokens) {
                joinedLine += token + " ";
            }
            expandedCode.push_back(joinedLine);
        }
    }

    return expandedCode;
}

// Função para processar macros
bool process_macros(vector<string>& lines) {
    vector<string> outputPre;
    map<string, Macro> macroTable; // Tabela de macros

    bool inMacroDefinition = false;
    string currentMacroName;
    Macro currentMacro;

    for (const string& line : lines) {
        if (line.empty()) { continue;}
        AssemblyLine l(line);
        if (l.getOperation() == "MACRO") {
            // Início da definição de uma macro
            inMacroDefinition = true;
            currentMacroName = l.getLabel();
            currentMacro.name = currentMacroName;
            currentMacro.parameters.clear();
            currentMacro.code.clear();
            vector<string> parameters = l.getOperands();
            for (const string& parameter : parameters) {
                currentMacro.parameters.push_back(parameter);
            }
        } else if (inMacroDefinition) {
            // Dentro da definição de macro, coletar o código da macro
            if (l.getOperation() == "ENDMACRO") {
                string label = l.getLabel();
                if (!label.empty()) {
                    currentMacro.code.push_back(label + ":");
                }

                inMacroDefinition = false;
                macroTable[currentMacroName] = currentMacro;
            } else {
                currentMacro.code.push_back(line);
            }
        } else {
            // Não estamos dentro de uma definição de macro
            if (macroTable.find(l.getOperation()) != macroTable.end()) { // Verificar se a linha contém uma chamada de macro
                string macroName = l.getOperation();
                vector<string> parameters = l.getOperands();
                for (const string& argument : parameters) {
                    currentMacro.parameters.push_back(argument);
                }
                vector<string> expandedCode = expandMacro(macroTable[macroName], parameters, macroTable);
                outputPre.insert(outputPre.end(), expandedCode.begin(), expandedCode.end());
            } else {
                outputPre.push_back(line);
            }
        }
    }

    lines = outputPre;

    return true;
}
