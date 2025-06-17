
typedef enum {
    NOP,    // No operation
    ADD,    // Add
    SUB,    // Subtract
    AND,    // Bitwise AND
    OR,     // Bitwise OR
    XOR,    // Bitwise XOR
    SHL,    // Shift left
    SHR,    // Shift right
    LUI,    // Load upper immediate
    AUIPC,  // Add upper immediate to PC
    JAL,    // Jump and link
    JALR,   // Jump and link register
    BEQ,    // Branch if equal
    BNE,    // Branch if not equal
    LW,     // Load word
    SW,     // Store word
} opcode_t;

typedef struct {
    opcode_t opcode;
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;
    int32_t imm;
} instruction_t;

