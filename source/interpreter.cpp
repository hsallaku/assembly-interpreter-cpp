#include <iostream>
#include <fstream>
#include <string>
#include <exception>

// Define the size of memory for simplicity
const int MEMORY_SIZE = 256;

class AssemblyInterpreter {
private:
    int accumulator = 0;
    int memory[MEMORY_SIZE] = {0};

public:
    AssemblyInterpreter() {
        // Initialize memory with some values for testing
        memory[0] = 10;
        memory[1] = 20;
        memory[2] = 5;
        memory[3] = 2;
    }

    void execute(const std::string& instruction, int operand) {
        if (instruction == "ADD") {
            accumulator += memory[operand];
        } else if (instruction == "SUB") {
            accumulator -= memory[operand];
        } else if (instruction == "MUL") {
            accumulator *= memory[operand];
        } else if (instruction == "DIV") {
            if (memory[operand] == 0) {
                throw std::runtime_error("Division by zero error");
            }
            accumulator /= memory[operand];
        } else if (instruction == "AND") {
            accumulator &= memory[operand];
        } else if (instruction == "OR") {
            accumulator |= memory[operand];
        } else if (instruction == "NOT") {
            accumulator = ~accumulator;
        } else if (instruction == "LD") {
            accumulator = memory[operand];
        } else if (instruction == "ST") {
            memory[operand] = accumulator;
        } else {
            throw std::runtime_error("Unknown instruction: " + instruction);
        }
    }

    void loadAndRun(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("File could not be opened: " + filename);
        }

        std::string line;
        while (getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;  // Skip empty lines and comments
            std::size_t spacePos = line.find(' ');
            std::string instruction = line.substr(0, spacePos);
            int operand = std::stoi(line.substr(spacePos + 1));
            execute(instruction, operand);
            std::cout << "Executed " << instruction << " " << operand << ", Accumulator: " << accumulator << std::endl;
        }

        file.close();
    }
};

int main() {
    const std::string filepath = "../instructions.txt";  // Hardcoded filename
    AssemblyInterpreter interpreter;
    try {
        interpreter.loadAndRun(filepath);
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
