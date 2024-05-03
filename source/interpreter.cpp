// Haki Sallaku & Thomas Scardino
// Dr. AbuMallouh
// CMPT334
// Optional Project - C++ Assembly Interpreter

// To add or change instructions, open ../instructions.txt
// Opcodes are ADD, SUB, MUL, DIV, AND, NOT, OR, LD, and ST
// Operands are 0, 1, 2, 3
// Formatting for each line should be OPCODE OPERAND, for example ADD 0

// To add or change operands, edit memory values in AssemblyInterpreter() below

#include <iostream>
#include <fstream>
#include <string>
#include <exception>

const int MEMORY_SIZE = 256;

class AssemblyInterpreter {
private:
    // One register - an accumulator
    int accumulator = 0;
    int memory[MEMORY_SIZE] = {0};

public:
    AssemblyInterpreter() {
        // Operands placed in memory
        memory[0] = 10;
        memory[1] = 20;
        memory[2] = 5;
        memory[3] = 2;
    }

    // Interprets assembly instruction opcodes outlined in the project document
    void execute(const std::string& opcode, int x) {
        if (opcode == "ADD") {
            // Add memory location X into accumulator
            accumulator += memory[x];
        } else if (opcode == "SUB") {
            // Subtract X from accumulator
            accumulator -= memory[x];
        } else if (opcode == "MUL") {
            // Multiply X with accumulator
            accumulator *= memory[x];
        } else if (opcode == "DIV") {
            if (memory[x] == 0) {
                // Catch for division by 0
                throw std::runtime_error("Division by zero error");
            }
            // Divide accumulator by X
            accumulator /= memory[x];
        } else if (opcode == "AND") {
            // And X with accumulator
            accumulator &= memory[x];
        } else if (opcode == "NOT") {
            // Complement accumulator
            accumulator = ~accumulator;
        } else if (opcode == "OR") {
            // Or X with accumulator
            accumulator |= memory[x];
        } else if (opcode == "LD") {
            // Load memory location X at accumulator
            accumulator = memory[x];
        } else if (opcode == "ST") {
            // Store accumulator at memory location X
            memory[x] = accumulator;
        } else {
            // Catch for incorrectly written instructions.txt
            throw std::runtime_error("Unknown opcode: " + opcode);
        }
    }

    void loadAndRun(const std::string& filename) {
        // Load instructions.txt
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("File could not be opened: " + filename);
        }

        // Header stating operands
        std::cout << "\nOperands in memory:\n\tMemory[0] = " << memory[0] << "\n\tMemory[1] = " << memory[1] << "\n\tMemory[2] = " << memory[2] << "\n\tMemory[3] = " << memory[3] << std::endl;
        std::string line;
        std::cout << "\nPerforming instructions from " << filename << "..." << std::endl;

        // Goes line by line in instructions.txt, splits the opcode from the x's memory location and uses them in execute()
        while (getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;  // Skip empty lines and comments
            std::size_t spacePos = line.find(' ');
            std::string opcode = line.substr(0, spacePos);
            int x = std::stoi(line.substr(spacePos + 1));
            execute(opcode, x);
            std::cout << "\tExecuted " << opcode << " " << memory[x] << ", Accumulator: " << accumulator << std::endl;
        }

        file.close();
    }
};

int main() {
    // Hardcoded filename
    const std::string filepath = "../instructions.txt";

    AssemblyInterpreter interpreter;
    try {
        interpreter.loadAndRun(filepath);
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
