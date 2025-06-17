
; Main loop
main_loop:
    LDA core.pc
    STA $00
    LDA core.pc+1
    STA $01
    LDA core.pc+2
    STA $02
    LDA progsize
    STA $04
    LDA progsize+1
    STA $05
    LDA progsize+2
    STA $06

    ; while (pc < progsize)
    LDA $00
    CMP $04
    BCS end_loop
    LDA $01
    SBC $05
    BCS end_loop
    LDA $02
    SBC $06
    BCS end_loop

    ; _op_ = (TU8*)&_prog_[pc]
    LDA $00
    STA $08
    LDA $01
    STA $09
    LDA $02
    STA $0A

    ; opcode = *_op_;
    LDA ($08), Y
    STA $0B

    ; switch (opcode & 0xF0)
    AND #$F0
    TAX

    ; Cases for the switch statement
    LDX #case_table_end - case_table
case_loop:
    DEX
    BEQ case_unknown
    CMP case_table, X
    BNE case_loop
    JMP (case_table+1, X)

case_table:
    .word R3_TYPE, case_r3
    .word R2_TYPE, case_r2
    .word RC_TYPE, case_rc
    .word RD_TYPE, case_rd
    .word I1_TYPE, case_i1
    .word IA_TYPE, case_ia
    .word I4_TYPE, case_i4
    .word IE_TYPE, case_ie
    .word SF_TYPE, case_sf
    .word SB_TYPE, case_sb
    .word S8_TYPE, case_s8
    .word U7_TYPE, case_u7
    .word U6_TYPE, case_u6
case_table_end:

; Placeholder for case_unknown
case_unknown:
    ; println("Unknown opcode type");
    JMP end_loop

; Placeholder for cases R3, R2, RC, RD, I1, IA, I4, IE, SF, SB, S8, U7, U6
; Implement the specific operations of each case in these sections
case_r3:
    ; ...
    JMP end_loop
case_r2:
    ; ...
    JMP end_loop
case_rc:
    ; ...
    JMP end_loop
case_rd:
    ; ...
    JMP end_loop
case_i1:
    ; ...
    JMP end_loop
case_ia:
    ; ...
    JMP end_loop
case_i4:
    ; ...
    JMP end_loop
case_ie:
    ; ...
    JMP end_loop
case_sf:
    ; ...
    JMP end_loop
case_sb:
    ; ...
    JMP end_loop
case_s8:
    ; ...
    JMP end_loop
case_u7:
    ; ...
    JMP end_loop
case_u6:
    ; ...
    JMP end_loop

end_loop:
    JMP main_loop

