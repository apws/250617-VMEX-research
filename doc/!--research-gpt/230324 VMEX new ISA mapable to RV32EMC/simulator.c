
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MEMORY_SIZE 0x10000

uint32_t memory[MEMORY_SIZE];
uint32_t registers[32] = {0};
uint32_t pc = 0;

uint32_t fetch() {
    uint32_t instruction = memory[pc / 4];
    pc += 4;
    return instruction;
}

void decode_and_execute(uint32_t instruction) {
    uint32_t opcode = instruction & 0x7F;
    uint32_t rd = (instruction >> 7) & 0x1F;
    uint32_t rs1 = (instruction >> 15) & 0x1F;
    uint32_t rs2 = (instruction >> 20) & 0x1F;
    uint32_t funct3 = (instruction >> 12) & 0x7;
    uint32_t funct7 = (instruction >> 25) & 0x7F;
    int32_t imm_I = (int32_t)(instruction & 0xFFF00000) >> 20;
    int32_t imm_S = ((instruction >> 25) & 0x7F) << 5 | ((instruction >> 7) & 0x1F);

    switch (opcode) {
        case 0x33: // R-type
            switch (funct3) {
                case 0x0: // add
                    registers[rd] = registers[rs1] + registers[rs2];
                    break;
                // Implement other R-type instructions
            }
            break;
        case 0x03: // I-type
            switch (funct3) {
                case 0x0: // lb
                    registers[rd] = memory[(registers[rs1] + imm_I) / 4];
                    break;
                // Implement other I-type instructions
            }
            break;
        case 0x23: // S-type
            switch (funct3) {
                case 0x0: // sb
                    memory[(registers[rs1] + imm_S) / 4] = registers[rs2];
                    break;
                // Implement other S-type instructions
            }
            break;
        // Implement other instruction types (U, UJ, B)
    }
}

void simulate() {
    while (1) {
        uint32_t instruction = fetch();
        decode_and_execute(instruction);
    }
}

int main() {
    // Initialize memory and registers
    // Load program into memory

    simulate();

    return 0;
}

