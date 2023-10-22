#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <limits> // Para usar numeric_limits

using namespace std;

// Variável global para representar a memória
vector<int> memory;

int dataStart = numeric_limits<int>::max();

map<int, pair<string, int>> instructionDictionary = {
    {1, {"ADD", 2}},
    {2, {"SUB", 2}},
    {3, {"MUL", 2}},
    {4, {"DIV", 2}},
    {5, {"JMP", 2}},
    {6, {"JMPN", 2}},
    {7, {"JMPP", 2}},
    {8, {"JMPZ", 2}},
    {9, {"COPY", 3}},
    {10, {"LOAD", 2}},
    {11, {"STORE", 2}},
    {12, {"INPUT", 2}},
    {13, {"OUTPUT", 2}},
    {14, {"STOP", 1}}
};

void executeInstruction(int opcode, int &accumulator, int &programCounter, int currentInstruction) {
    switch (opcode) {
        case 1: // ADD
            accumulator += memory[memory[programCounter + 1]];
            break;
        case 2: // SUB
            accumulator -= memory[memory[programCounter + 1]];
            break;
        case 3: // MUL
            accumulator *= memory[memory[programCounter + 1]];
            break;
        case 4: // DIV
            if (memory[memory[programCounter + 1]] != 0) {
                accumulator /= memory[memory[programCounter + 1]];
            } else {
                cerr << "Erro: Divisao por zero" << endl;
                programCounter = -2; // Suspende a execução
            }
            break;
        case 5: // JMP
            programCounter = memory[programCounter + 1];
            break;
        case 6: // JMPN
            if (accumulator < 0) {
                programCounter = memory[programCounter + 1];
            } else {
                programCounter += instructionDictionary[currentInstruction].second;
            }
            break;
        case 7: // JMPP
            if (accumulator > 0) {
                programCounter = memory[programCounter + 1];
            } else {
                programCounter += instructionDictionary[currentInstruction].second;
            }
            break;
        case 8: // JMPZ
            if (accumulator == 0) {
                programCounter = memory[programCounter + 1];
            } else {
                programCounter += instructionDictionary[currentInstruction].second;
            }
            break;
        case 9: // COPY
            memory[memory[programCounter + 2]] = memory[memory[programCounter + 1]];
            break;
        case 10: // LOAD
            accumulator = memory[memory[programCounter + 1]];
            break;
        case 11: // STORE
            memory[memory[programCounter + 1]] = accumulator;
            break;
        case 12: // INPUT
            cout << "Digite um valor: ";
            cin >> memory[memory[programCounter + 1]];
            break;
        case 13: // OUTPUT
            cout << "Saida: " << memory[memory[programCounter + 1]] << endl;
            break;
        case 14: // STOP
            programCounter = -2; // Suspende a execução
            break;
        default:
            cerr << "Instrucao invalida" << endl;
            programCounter = -2; // Suspende a execução
    }
}

void loadInstructionsFromFile(const string &filename) {
    ifstream inputFile(filename);

    int opcode;
    int pc = 0; // Contador do Program Counter

    while (inputFile >> opcode) {
        memory.push_back(opcode);
        pc++;

        bool isJump = opcode >= 5 && opcode <= 8;
        int numOperands = instructionDictionary[opcode].second - 1;

        for (int i = 0; i < numOperands; ++i) {
            int operand;
            inputFile >> operand;
            pc++;
            memory.push_back(operand);

            // Atualiza o início da seção de dados se o operando for menor
            if (operand < dataStart && !isJump) {
                dataStart = operand;
            }
        }

        if (pc >= dataStart - 1) {
            while (inputFile >> opcode) {
                memory.push_back(opcode); // Continua lendo e armazenando na memória (seção de dados)
            }
        }
    }

    inputFile.close();
}


void printDataMemory(const vector<int> &memory, int dataStart) {
    cout << "Secao de dados da memoria:" << endl;
    for (int i = dataStart; i < memory.size(); ++i) {
        cout << "M[" << i << "] = " << memory[i] << "; ";
    }
    cout << endl;
}

void displayCurrentInstruction(int programCounter, int currentInstruction) {
    string assemblyInstruction = "INVALID";

    if (currentInstruction >= 1 && currentInstruction <= 14) {
        assemblyInstruction = instructionDictionary[currentInstruction].first;
    }

    if (currentInstruction == 14) {
        cout << assemblyInstruction;
        programCounter = -1;
    } else if (currentInstruction >= 1 && currentInstruction <= 13) {
        programCounter++;
        int operand1 = memory[programCounter];
        cout << assemblyInstruction << " " << operand1;

        if (currentInstruction == 9) { // COPY
            programCounter++;
            int operand2 = memory[programCounter];
            cout << " " << operand2;
        }
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "CAMINHO NAO FORNECIDO" << endl;
        cerr << "Uso correto: " << argv[0] << " <arquivo.obj>" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        return 1;
    }

    loadInstructionsFromFile(filename);

    int accumulator = 0;
    int programCounter = 0;

    // Simule a execução das instruções da memória
    while (programCounter >= 0 && programCounter < 1000) {
        int programCounterInstruction = programCounter;
        int currentInstruction = memory[programCounter];
        bool isJump = currentInstruction >= 5 && currentInstruction <= 8;

        displayCurrentInstruction(programCounter, currentInstruction);

        executeInstruction(currentInstruction, accumulator, programCounter, currentInstruction);

        if (!isJump) {
            programCounter += instructionDictionary[currentInstruction].second;
        }
        if (programCounter >= dataStart) {
            cout << "PC <- " << programCounter << " ACC <- " << accumulator << endl;
            cerr << "SEGMENTATION FAULT" << endl;
            programCounter = -1; // Suspend the execution
        }

        cout << "PC <- " << programCounter << " ACC <- " << accumulator << endl;

//        printDataMemory(memory, dataStart);
        cout << endl;

        // Espera o usuário pressionar ENTER para executar a próxima linha
        cin.get();
    }

    return 0;
}
