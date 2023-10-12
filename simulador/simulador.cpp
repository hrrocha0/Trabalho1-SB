#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

// Variável global para representar a memória
vector<int> memory;

int dataStart = -1;

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
    bool dataSection = false;

    while (inputFile >> opcode) {
        if (opcode == 14) { // Verificar se a instrução é STOP (14)
            dataStart = memory.size() + 1; // Início da seção de dados
        }

        memory.push_back(opcode);
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
