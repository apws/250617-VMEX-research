
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

    INY
    LDA ($08),Y
    LSR
    LSR
    LSR
    LSR
    STA $0E
    JMP continue_loop

; I-Type parsing
parse_i_type:
    ; rd  = _op_[1] >> 4;
    INY
    LDA ($08),Y
    LSR
    LSR
    LSR
    LSR
    STA $0C

    ; rs1
