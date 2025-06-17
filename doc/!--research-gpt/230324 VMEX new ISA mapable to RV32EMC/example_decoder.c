void decode_and_execute(instruction_t instr) {
    switch (instr.opcode) {
        case NOP:
            break;
        case ADD:
            registers[instr.rd] = registers[instr.rs1] + registers[instr.rs2];
            break;
        // Implement the remaining instructions
    }
}

