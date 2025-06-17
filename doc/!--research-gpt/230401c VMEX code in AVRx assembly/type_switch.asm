
//asi to neni uplne dobre, ale dobrej zaklad pro to co pouzit '!!!!!!!!!!!


; Assuming the following zero page locations for the variables
; pc      : $00
; _prog_  : $02
; _op_    : $04
; opcode  : $06
; rd      : $08
; rs1     : $09
; rs2     : $0A
; imm     : $0C

; TU8* _op_ = (TU8*)&_prog_[pc];
    lda pc          ; Load lower byte of pc into A
    sta $fe         ; Temporarily store it in $fe
    lda pc+1        ; Load higher byte of pc into A
    sta $ff         ; Temporarily store it in $ff
    lda _prog_      ; Load lower byte of _prog_ into A
    clc             ; Clear carry flag for addition
    adc $fe         ; Add lower byte of pc
    sta _op_        ; Store the result as the lower byte of _op_
    lda _prog_+1    ; Load higher byte of _prog_ into A
    adc $ff         ; Add higher byte of pc with carry
    sta _op_+1      ; Store the result as the higher byte of _op_

; opcode = *_op_;
    ldy #0          ; Set Y to 0 as an offset
    lda (_op_),y    ; Load the value pointed by _op_ (indirect indexed addressing)
    sta opcode      ; Store the value in opcode

; opcode & 0xF0
    lda opcode
    and #$F0
    sta $fd         ; Temporarily store the result in $fd for the switch statement

; switch (opcode & 0xF0)
switch_start:
    lda $fd
    cmp #R3_TYPE
    beq case_r3_r2_rc_rd
    cmp #R2_TYPE
    beq case_r3_r2_rc_rd
    cmp #RC_TYPE
    beq case_r3_r2_rc_rd
    cmp #RD_TYPE
    beq case_r3_r2_rc_rd

    cmp #I1_TYPE
    beq case_i1_ia_i4_ie
    cmp #IA_TYPE
    beq case_i1_ia_i4_ie
    cmp #I4_TYPE
    beq case_i1_ia_i4_ie
    cmp #IE_TYPE
    beq case_i1_ia_i4_ie

    cmp #SF_TYPE
    beq case_sf_sb_s8
    cmp #SB_TYPE
    beq case_sf_sb_s8
    cmp #S8_TYPE
    beq case_sf_sb_s8

    cmp #U7_TYPE
    beq case_u7_u6
    cmp #U6_TYPE
    beq case_u7_u6
    jmp unknown_type

; case R3_TYPE:
; case R2_TYPE:
; case RC_TYPE:
; case RD_TYPE:
case_r3_r2_rc_rd:
; Assuming the following register mapping for the variables
; _op_  : R20, R21 (pointer, 16-bit)
; rd    : R22
; rs1   : R23
; rs2   : R24
; Y     : R28, R29 (Y pointer, 16-bit)

; Load _op_[1] into rd
    adiw R20, 1           ; Increment _op_ pointer by 1
    ld  R22, Y+           ; Load the value pointed by _op_ (post-increment indirect) into rd
    swap R22              ; Swap nibbles of rd
    andi R22, 0x0F        ; Clear upper nibble of rd (ensure upper nibble is zero)

; Load _op_[2] into rs1
    ld  R23, Y+           ; Load the value pointed by _op_ (post-increment indirect) into rs1
    swap R23              ; Swap nibbles of rs1
    andi R23, 0x0F        ; Clear upper nibble of rs1 (ensure upper nibble is zero)

; Load _op_[3] into rs2
    ld  R24, Y+           ; Load the value pointed by _op_ (post-increment indirect) into rs2
    swap R24              ; Swap nibbles of rs2
    andi R24, 0x0F        ; Clear upper nibble of rs2 (ensure upper nibble is zero)

; The break statement is not needed in assembly since it is used for control flow in C.

    jmp switch_end

; case I1_TYPE:
; case IA_TYPE:
; case I4_TYPE:
; case IE_TYPE:
case_i1_ia_i4_ie:
; Assuming the following register mapping for the variables
; _op_  : R20, R21 (pointer, 16-bit)
; rd    : R22
; rs1   : R23
; imm   : R24, R25 (16-bit)
; Y     : R28, R29 (Y pointer, 16-bit)

; Load _op_[1] into rd and rs1
    adiw R20, 1           ; Increment _op_ pointer by 1
    ld  R22, Y+           ; Load the value pointed by _op_ (post-increment indirect) into rd

; Calculate rd = _op_[1] >> 4
    mov R23, R22          ; Copy the value of rd to rs1
    swap R22              ; Swap nibbles of rd
    andi R22, 0x0F        ; Clear upper nibble of rd (ensure upper nibble is zero)

; Calculate rs1 = _op_[1] & 0xF
    andi R23, 0x0F        ; Logical AND with 0x0F to keep the lower 4 bits

; Load 16-bit immediate value (imm = (_op_[2] << 8) | _op_[3])
    ld  R25, Y+           ; Load the value pointed by _op_ (post-increment indirect) into imm (high byte)
    ld  R24, Y+           ; Load the value pointed by _op_ (post-increment indirect) into imm (low byte)

    jmp switch_end


case_sf_sb_s8:
; Assuming the following register mapping for the variables
; _op_  : R20, R21 (pointer, 16-bit)
; rs1   : R22
; rs2   : R23
; imm   : R24, R25 (16-bit)
; Y     : R28, R29 (Y pointer, 16-bit)

; Load _op_[1] into rs1 and rs2
    adiw R20, 1           ; Increment _op_ pointer by 1
    ld  R22, Y+           ; Load the value pointed by _op_ (post-increment indirect) into rs1

; Calculate rs1 = _op_[1] >> 4
    mov R23, R22          ; Copy the value of rs1 to rs2
    swap R22              ; Swap nibbles of rs1
    andi R22, 0x0F        ; Clear upper nibble of rs1 (ensure upper nibble is zero)

; Calculate rs2 = _op_[1] & 0xF
    andi R23, 0x0F        ; Logical AND with 0x0F to keep the lower 4 bits

; Load 16-bit immediate value (imm = (_op_[2] << 8) | _op_[3])
    ld  R25, Y+           ; Load the value pointed by _op_ (post-increment indirect) into imm (high byte)
    ld  R24, Y+           ; Load the value pointed by _op_ (post-increment indirect) into imm (low byte)

    jmp switch_end


case_u7_u6:
; Assuming the following register mapping for the variables
; _op_  : R20, R21 (pointer, 16-bit)
; rd    : R22
; imm   : R24, R25 (16-bit)
; Y     : R28, R29 (Y pointer, 16-bit)

; Load _op_[1] into rd
    adiw R20, 1           ; Increment _op_ pointer by 1
    ld  R22, Y+           ; Load the value pointed by _op_ (post-increment indirect) into rd

; Calculate rd = _op_[1] >> 4
    swap R22              ; Swap nibbles of rd
    andi R22, 0x0F        ; Clear upper nibble of rd (ensure upper nibble is zero)

; Load 16-bit immediate value (imm = (_op_[2] << 8) | _op_[3])
    ld  R25, Y+           ; Load the value pointed by _op_ (post-increment indirect) into imm (high byte)
    ld  R24, Y+           ; Load the value pointed by _op_ (post-increment indirect) into imm (low byte)

    jmp switch_end


switch_end:

