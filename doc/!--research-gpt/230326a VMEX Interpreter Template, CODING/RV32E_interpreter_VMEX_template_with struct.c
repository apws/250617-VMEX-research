#include <stdint.h>
#include <stdio.h>

#define PAGE_SIZE 256
#define PROG_SIZE PAGE_SIZE * 1
#define DATA_SIZE PAGE_SIZE * 1

// Define RV32E instruction format types
typedef enum {
    S_TYPE,
    U_TYPE,
    I_TYPE,
    R_TYPE,
    UNKNOWN_TYPE
} InstructionFormatType;

// Define memory struct
typedef struct {
    uint32_t regs[58];
    uint32_t opcode;
    uint32_t rs1;
    uint32_t rs2;
    uint32_t rd;
    uint32_t imm;
    uint32_t pc;
    uint32_t prog[PROG_SIZE]; // Replace with actual instructions and appropriate size
    uint32_t data[DATA_SIZE];
} Memory;

// Function prototypes
InstructionFormatType decode_instruction_format(uint32_t instruction);
void execute_instruction(Memory *memory);

int main() {
    Memory memory = {0}; // Initialize memory to all zeros

    while (memory.pc < PROG_SIZE) {
        uint32_t instruction = memory.prog[memory.pc];
        InstructionFormatType format = decode_instruction_format(instruction);
        execute_instruction(&memory);

        memory.pc++; // Increment the PC
    }

    return 0;
}

InstructionFormatType decode_instruction_format(uint32_t instruction) {
    uint32_t format_code = (instruction >> 5) & 0x7; // Extract bits 7-5

    switch (format_code) {
        case 0: return S_TYPE;
        case 1: return U_TYPE;
        case 2: return I_TYPE;
        case 3: return R_TYPE;
        default: return UNKNOWN_TYPE;
    }
}

void execute_instruction(Memory *memory) {
    switch (decode_instruction_format(memory->prog[memory->pc])) {
        case S_TYPE:
            memory->rs1 = (memory->prog[memory->pc] >> 12) & 0xF;
            memory->rs2 = (memory->prog[memory->pc] >> 8) & 0xF;
            memory->imm = ((memory->prog[memory->pc] >> 25) << 5) | ((memory->prog[memory->pc] >> 7) & 0x1F);
            memory->opcode = memory->prog[memory->pc] & 0x1F;
            // Perform the S-type instruction based on the opcode
            switch (memory->opcode) {
                case 0x0: // sb
                    memory->data[memory->regs[memory->rs1] + memory->imm] = memory->regs[memory->rs2] & 0xFF;
                    break;

                case 0x1: // sh
                    memory->data[memory->regs[memory->rs1] + memory->imm] = memory->regs[memory->rs2] & 0xFF;
                    memory->data[memory->regs[memory->rs1] + memory->imm + 1] = (memory->regs[memory->rs2] >> 8) & 0xFF;
                    break;

                case 0x2: // sw
                    memory->data[memory->regs[memory->rs1] + memory->imm] = memory->regs[memory->rs2] & 0xFF;
                    memory->data[memory->regs[memory->rs1] + memory->imm + 1] = (memory->regs[memory->rs2] >> 8) & 0xFF;
                    memory->data[memory->regs[memory->rs1] + memory->imm + 2] = (memory->regs[memory->rs2] >> 16) & 0xFF;
                    memory->data[memory->regs[memory->rs1] + memory->imm + 3] = (memory->regs[memory->rs2] >> 24) & 0xFF;
                    break;

                case 0x0: // beq
                    if (memory->regs[memory->rs1] == memory->regs[memory->rs2]) {
                        memory->pc += (int32_t) memory->imm;
                    }
                    break;

                case 0x1: // bne
                    if (memory->regs[memory->rs1] != memory->regs[memory->rs2]) {
                        memory->pc += (int32_t) memory->imm;
                    }
                    break;

                case 0x4: // blt
                    if ((int32_t) memory->regs[memory->rs1] < (int32_t) memory->regs[memory->rs2]) {
                        memory->pc += (int32_t) memory->imm;
                    }
                    break;

                case 0x5: // bge
                    if ((int32_t) memory->regs[memory->rs1] >= (int32_t) memory->regs[memory->rs2]) {
                        memory->pc += (int32_t) memory->imm;
                    }
                    break;

                case 0x6: // bltu
                    if (memory->regs[memory->rs1] < memory->regs[memory->rs2]) {
                        memory->pc += (int32_t) memory->imm;
                    }
                    break;

                case 0x7: // bgeu
                    if (memory->regs[memory->rs1] >= memory->regs[memory->rs2]) {
                        memory->pc += (int32_t) memory->imm;
                    }
                    break;

                default:
                    printf("Unknown S-type opcode: 0x%x\n", memory->opcode);
                    break;
            }
            break;

        case U_TYPE:
            memory->rd = (memory->prog[memory->pc] >> 8) & 0xF;
            memory->imm = (memory->prog[memory->pc] >> 16) & 0xFFFF;
            memory->opcode = memory->prog[memory->pc] & 0x1F;
            // Perform the U-type instruction based on the opcode
            switch (memory->opcode) {
                case 0x0: // lui
                    memory->regs[memory->rd] = (uint32_t) memory->imm << 12;
                    break;

                case 0x1: // auipc
                    memory->regs[memory->rd] = ((uint32_t) memory->imm << 12) + memory->pc;
                    break;

                case 0x1B: // jal
                    memory->regs[memory->rd] = memory->pc + 4;
                    memory->pc += (int32_t) memory->imm;
                    break;

                default:
                    printf("Unknown U-type opcode: 0x%x\n", memory->opcode);
                    break;
            }
            break;

        case I_TYPE:
            memory->rs1 = (memory->prog[memory->pc] >> 12) & 0xF;
            memory->rd = (memory->prog[memory->pc] >> 8) & 0xF;
            memory->imm = (memory->prog[memory->pc] >> 16) & 0xFFFF;
            memory->opcode = memory->prog[memory->pc] & 0x1F;
            // Perform the I-type instruction based on the opcode
            switch (memory->opcode) {
                case 0x0: // addi
                    memory->regs[memory->rd] = memory->regs[memory->rs1] + (int32_t) memory->imm;
                    break;

                case 0x1: // slli
                    memory->regs[memory->rd] = memory->regs[memory->rs1] << (memory->imm & 0x1F);
                    break;

                case 0x2: // slti
                    memory->regs[memory->rd] = (int32_t) memory->regs[memory->rs1] < (int32_t) memory->imm;
                    break;

                case 0x3: // sltiu
                    memory->regs[memory->rd] = memory->regs[memory->rs1] < memory->imm;
                    break;

                case 0x4: // xori
                    memory->regs[memory->rd] = memory->regs[memory->rs1] ^ memory->imm;
                    break;

                case 0x5: // srli or srai
                    if ((memory->imm >> 5) & 0x1) {
                        // srai
                        memory->regs[memory->rd] = (int32_t) memory->regs[memory->rs1] >> (memory->imm & 0x1F);
                    } else {
                        // srli
                        memory->regs[memory->rd] = memory->regs[memory->rs1] >> (memory->imm & 0x1F);
                    }
                    break;

                case 0x6: // ori
                    memory->regs[memory->rd] = memory->regs[memory->rs1] | memory->imm;
                    break;

                case 0x7: // andi
                    memory->regs[memory->rd] = memory->regs[memory->rs1] & memory->imm;
                    break;

                case 0x0: // lb
                    memory->regs[memory->rd] = (int8_t) memory->data[memory->regs[memory->rs1] + memory->imm];
                    break;

                case 0x1: // lh
                    memory->regs[memory->rd] = (int16_t) ((memory->data[memory->regs[memory->rs1] + memory->imm] << 0) |
                                                            (memory->data[memory->regs[memory->rs1] + memory->imm + 1] << 8));
                    break;

                case 0x2: // lw
                    memory->regs[memory->rd] = (int32_t) ((memory->data[memory->regs[memory->rs1] + memory->imm] << 0) |
                                                            (memory->data[memory->regs[memory->rs1] + memory->imm + 1] << 8) |
                                                            (memory->data[memory->regs[memory->rs1] + memory->imm + 2] << 16) |
                                                            (memory->data[memory->regs[memory->rs1] + memory->imm + 3] << 24));
                    break;

                case 0x4: // lbu
                    memory->regs[memory->rd] = memory->data[memory->regs[memory->rs1] + memory->imm] & 0xFF;
                    break;

                case 0x5: // lhu
                    memory->regs[memory->rd] = ((memory->data[memory->regs[memory->rs1] + memory->imm] << 0) |
                                                (memory->data[memory->regs[memory->rs1] + memory->imm + 1] << 8)) & 0xFFFF;
                    break;

                case 0x67: // jalr
                    memory->regs[memory->rd] = memory->pc + 4;
                    memory->pc = (memory->regs[memory->rs1] + memory->imm) & ~0x1;
                    break;

                case 0x73: // ecall and ebreak
                    if (memory->imm == 0) {
                        // Execute the system call
                        printf("System call!\n");
                    } else if (memory->imm == 1) {
                        // Execute the break instruction
                        printf("Breakpoint!\n");
                    } else {
                        printf("Unknown instruction\n");
                    }
                    break;

                default:
                    printf("Unknown I-type opcode: 0x%x\n", memory->opcode);
                    break;
            }
            break;

        case R_TYPE:
            memory->rs1 = (memory->prog[memory->pc] >> 16) & 0xF;
            memory->rs2 = (memory->prog[memory->pc] >> 24) & 0xF;
            memory->rd = (memory->prog[memory->pc] >> 8) & 0xF;
            memory->opcode = memory->prog[memory->pc] & 0x1F;
            // Perform the R-type instruction based on the opcode
            switch (memory->opcode) {
                case 0x0: // add
                    memory->regs[memory->rd] = memory->regs[memory->rs1] + memory->regs[memory->rs2];
                    break;

                case 0x1: // sub
                    memory->regs[memory->rd] = memory->regs[memory->rs1] - memory->regs[memory->rs2];
                    break;

                case 0x2: // and
                    memory->regs[memory->rd] = memory->regs[memory->rs1] & memory->regs[memory->rs2];
                    break;

                case 0x3: // or
                    memory->regs[memory->rd] = memory->regs[memory->rs1] | memory->regs[memory->rs2];
                    break;

                case 0x4: // xor
                    memory->regs[memory->rd] = memory->regs[memory->rs1] ^ memory->regs[memory->rs2];
                    break;

                case 0x5: // sll
                    memory->regs[memory->rd] = memory->regs[memory->rs1] << (memory->regs[memory->rs2] & 0x1F);
                    break;

                case 0x6: // srl
                    memory->regs[memory->rd] = memory->regs[memory->rs1] >> (memory->regs[memory->rs2] & 0x1F);
                    break;

                case 0x7: // sra
                    memory->regs[memory->rd] = (int32_t) memory->regs[memory->rs1] >> (memory->regs[memory->rs2] & 0x1F);
                    break;

                case 0x8: // slt
                    memory->regs[memory->rd] = (int32_t) memory->regs[memory->rs1] < (int32_t) memory->regs[memory->rs2];
                    break;

                case 0x9: // sltu
                    memory->regs[memory->rd] = memory->regs[memory->rs1] < memory->regs[memory->rs2];
                    break;

                case 0x8: // jr
                    memory->pc = memory->regs[memory->rs1];
                    break;

                default:
                    printf("Unknown R-type opcode: 0x%x\n", memory->opcode);
                    break;
            }
            break;

        case UNKNOWN_TYPE:
        default:
            printf("Unknown instruction format\n");
            break;
    }
}
