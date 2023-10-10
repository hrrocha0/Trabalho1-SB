#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Variável global para representar a memória
vector<int> memory(1000, 0); // Memória com 1000 locais de armazenamento

// Estrutura para representar uma instrução
struct Instruction {
    int opcode;
    int operand1; // Primeiro operando (para instruções com 2 operandos)
    int operand2; // Segundo operando (para instruções com 2 operandos)
};

// Função para imprimir o estado atual da memória
void printMemoryState() {
    cout << "Estado atual da memória:\n";
    for (int i = 0; i < 32; i++) {
        cout << "[" << i << "]: " << memory[i] << "\t";
        if ((i + 1) % 10 == 0) {
            cout << endl;
        }
    }
    cout << endl;
    cout << endl;
}

// Função para obter a representação em assembly de uma instrução
string getAssembly(Instruction instr) {
    switch (instr.opcode) {
        case 1: return "ADD";
        case 2: return "SUB";
        case 3: return "MUL";
        case 4: return "DIV";
        case 5: return "JMP";
        case 6: return "JMPN";
        case 7: return "JMPP";
        case 8: return "JMPZ";
        case 9: return "COPY";
        case 10: return "LOAD";
        case 11: return "STORE";
        case 12: return "INPUT";
        case 13: return "OUTPUT";
        case 14: return "STOP";
        default: return "INVALID";
    }
}

// Função para executar uma instrução
void executeInstruction(Instruction instr, int &accumulator, int &programCounter) {
    switch (instr.opcode) {
        case 1: // ADD
            accumulator += memory[instr.operand1];
            break;
        case 2: // SUB
            accumulator -= memory[instr.operand1];
            break;
        case 3: // MUL
            accumulator *= memory[instr.operand1];
            break;
        case 4: // DIV
            if (memory[instr.operand1] != 0) {
                accumulator /= memory[instr.operand1];
            } else {
                cerr << "Erro: Divisão por zero" << endl;
                programCounter = -1; // Suspende a execução
                return;
            }
            break;
        case 5: // JMP
            programCounter = instr.operand1;
            return;
        case 6: // JMPN
            if (accumulator < 0) {
                programCounter = instr.operand1;
                return;
            }
            break;
        case 7: // JMPP
            if (accumulator > 0) {
                programCounter = instr.operand1;
                return;
            }
            break;
        case 8: // JMPZ
            if (accumulator == 0) {
                programCounter = instr.operand1;
                return;
            }
            break;
        case 9: // COPY
            memory[instr.operand2] = memory[instr.operand1];
            break;
        case 10: // LOAD
            accumulator = memory[instr.operand1];
            break;
        case 11: // STORE
            memory[instr.operand1] = accumulator;
            break;
        case 12: // INPUT
            cout << "Digite um valor: ";
            cin >> memory[instr.operand1];
            break;
        case 13: // OUTPUT
            cout << "Saída: " << memory[instr.operand1] << endl << "\n";
            break;
        case 14: // STOP
            programCounter = -1; // Suspende a execução
            break;
        default:
            cerr << "Instrução inválida" << endl;
            programCounter = -1; // Suspende a execução
            return;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <arquivo.obj>" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        return 1;
    }

    int accumulator = 0;
    int programCounter = 0;
    vector<Instruction> program; // Armazena as instruções do programa OBJETO

    // Ler as instruções do arquivo externo e carregá-las no vetor 'program'
int opcode, operand1, operand2;
bool dataSection = false;

while (inputFile >> opcode) {
    if (opcode == 14) { // Verificar se a instrução é STOP (14)
        dataSection = true;
        programCounter++;
    } else if (dataSection) {

        memory[programCounter] = opcode;
        cout << programCounter << "-" << memory[programCounter] << "\n";
        programCounter++;
    } else {
        Instruction instr;
        instr.opcode = opcode;
        switch (opcode) {
            case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 10: case 11: case 12: case 13:
                inputFile >> instr.operand1;
                cout << "instr" << instr.opcode << " " << instr.operand1 << "\n";
                programCounter += 2;
                break;
            case 9: // COPY
                inputFile >> instr.operand1 >> instr.operand2;
                cout << "instr" << instr.opcode << " " << instr.operand1 << " " << instr.operand2 << "\n";
                programCounter += 3;
                break;
            default:
                cerr << "Instrução inválida" << endl;
                programCounter = -1; // Suspende a execução
                return 1;
        }
        program.push_back(instr);
    }
}

    programCounter = 0;

    inputFile.close();

    // Simule a execução das instruções
    while (programCounter >= 0 && programCounter < program.size()) {
        Instruction currentInstruction = program[programCounter];
        string assemblyInstruction = getAssembly(currentInstruction);

        cout << "PC <- " << programCounter << " ACC <- " << accumulator << endl;

        if (currentInstruction.opcode != 9) { // Se for COPY, imprima os operandos
            cout << assemblyInstruction << " " << currentInstruction.operand1;
        }
        if (currentInstruction.opcode == 9) { // Se for COPY, imprima os operandos
            cout << assemblyInstruction << " " << currentInstruction.operand1 << " " << currentInstruction.operand2;
        }
        cout << endl;

        executeInstruction(currentInstruction, accumulator, programCounter);

        printMemoryState();

        // Espera o usuário pressionar ENTER para executar a próxima linha
        cin.get();

        programCounter++; // Atualize o PC para a próxima instrução
    }

    return 0;
}
