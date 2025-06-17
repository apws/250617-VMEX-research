
    ; Load opcode from _op_ address
    LDA (_op_), Y
    STA opcode

    ; Calculate opcode & 0xF0
    AND #$F0

    ; Store the result in temp8
    STA temp8

; Switch statement begins
switch_start:

    ; Case R3_TYPE, R2_TYPE, RC_TYPE, RD_TYPE
    LDA temp8
    CMP #R3_TYPE
    BEQ r_case
    CMP #R2_TYPE
    BEQ r_case
    CMP #RC_TYPE
    BEQ r_case
    CMP #RD_TYPE
    BEQ r_case
    JMP next_case

r_case:
    ; rd  = _op_[1] >> 4;
    LDY #1
    LDA (_op_), Y
    LSR
    LSR
    LSR
    LSR
    STA rd

    ; rs1 = _op_[2] >> 4;
    LDY #2
    LDA (_op_), Y
    LSR
    LSR
    LSR
    LSR
    STA rs1

    ; rs2 = _op_[3] >> 4;
    LDY #3
    LDA (_op_), Y
    LSR
    LSR
    LSR
    LSR
    STA rs2

    JMP switch_end

; Next case
next_case:

    ; Case I1_TYPE, IA_TYPE, I4_TYPE, IE_TYPE
    LDA temp8
    CMP #I1_TYPE
    BEQ i_case
    CMP #IA_TYPE
    BEQ i_case
    CMP #I4_TYPE
    BEQ i_case
    CMP #IE_TYPE
    BEQ i_case
    JMP next_case_2

i_case:
    ; rd  = _op_[1] >> 4;
    LDY #1
    LDA (_op_), Y
    LSR
    LSR
    LSR
    LSR
    STA rd

    ; rs1 = _op_[1] & 0xF;
    LDY #1
    LDA (_op_), Y
    AND #$0F
    STA rs1

    ; imm = *((TU16 *) (_op_ + 2)); // Read 16-bit immediate value directly
    LDY #2
    LDA (_op_), Y
    STA imm
    LDY #3
    LDA (_op_), Y
    STA imm+1

    JMP switch_end

; Next case
next_case_2:

    ; Case SF_TYPE, SB_TYPE, S8_TYPE
    LDA temp8
    CMP #SF_TYPE
    BEQ s_case
    CMP #SB_TYPE
    BEQ s_case
    CMP #S8_TYPE
    BEQ s_case
    JMP next_case_3

s_case:
    ; rs1 = _op_[1] >> 4;
    LDY #1
    LDA (_op_), Y
    LSR
    LSR
    LSR
    LSR
    STA rs1

    ; rs2 = _op_[1] & 0xF;
    LDY #1
    LDA (_op_), Y
    AND #$0F
    STA rs2

    ; imm = *((TU16 *) (_op_ + 2)); // Read 16-bit immediate value directly
    LDY #2
    LDA (_op_), Y
    STA imm
    LDY #3
    LDA (_op_), Y
    STA imm+1

    JMP switch_end

; Next case
next_case_3:

    ; Case U7_TYPE, U6_TYPE
    LDA temp8
    CMP #U7_TYPE
    BEQ u_case
    CMP #U6_TYPE
    BEQ u_case
    JMP unknown_case

u_case:
    ; rd  = _op_[1] >> 4;
    LDY #1
    LDA (_op_), Y
    LSR
    LSR
    LSR
    LSR
