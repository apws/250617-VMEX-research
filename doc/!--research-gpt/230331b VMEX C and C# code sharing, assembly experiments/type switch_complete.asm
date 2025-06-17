
        //parameters parsing
        TU8* _op_ = (TU8*)&_prog_[pc];
        opcode = *_op_;


; Assuming the following zero page locations for the variables
; pc      : $00
; _prog_  : $02
; _op_    : $04
; opcode  : $06

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






                rd  = _op_[1] >> 4;
                rs1 = _op_[2] >> 4;
                rs2 = _op_[3] >> 4;
                break;


; Assuming the following zero page locations for the variables
; _op_  : $04
; rd    : $08
; rs1   : $09
; rs2   : $0A

; Load _op_[1] into rd
    ldy #1          ; Set Y to 1 as an offset
    lda (_op_),y    ; Load the value pointed by _op_ + 1 (indirect indexed addressing)
    lsr             ; Shift right 4 bits (divide by 16)
    lsr
    lsr
    lsr
    sta rd          ; Store the result in rd

; Load _op_[2] into rs1
    iny             ; Increment Y to 2
    lda (_op_),y    ; Load the value pointed by _op_ + 2 (indirect indexed addressing)
    lsr             ; Shift right 4 bits (divide by 16)
    lsr
    lsr
    lsr
    sta rs1         ; Store the result in rs1

; Load _op_[3] into rs2
    iny             ; Increment Y to 3
    lda (_op_),y    ; Load the value pointed by _op_ + 3 (indirect indexed addressing)
    lsr             ; Shift right 4 bits (divide by 16)
    lsr
    lsr
    lsr
    sta rs2         ; Store the result in rs2

; The break statement is not needed in assembly since it is used for control flow in C.




                rd  = _op_[1] >> 4;
                rs1 = _op_[1] & 0xF;
                imm = *((TU16 *) (_op_ + 2)); // Read 16-bit immediate value directly


; Assuming the following zero page locations for the variables
; _op_  : $04
; rd    : $08
; rs1   : $09
; imm   : $0A

; Load _op_[1] into rd and rs1
    ldy #1          ; Set Y to 1 as an offset
    lda (_op_),y    ; Load the value pointed by _op_ + 1 (indirect indexed addressing)

; Calculate rd = _op_[1] >> 4
    pha             ; Push the loaded value onto the stack
    lsr             ; Shift right 4 bits (divide by 16)
    lsr
    lsr
    lsr
    sta rd          ; Store the result in rd

; Calculate rs1 = _op_[1] & 0xF
    pla             ; Pull the value from the stack
    and #$0F        ; Logical AND with 0x0F to keep the lower 4 bits
    sta rs1         ; Store the result in rs1

; Load 16-bit immediate value (imm = *((TU16 *) (_op_ + 2)))
    iny             ; Increment Y to 2
    lda (_op_),y    ; Load the value pointed by _op_ + 2 (indirect indexed addressing)
    sta imm         ; Store the lower byte of imm
    iny             ; Increment Y to 3
    lda (_op_),y    ; Load the value pointed by _op_ + 3 (indirect indexed addressing)
    sta imm+1       ; Store the higher byte of imm




                rs1 = _op_[1] >> 4;
                rs2 = _op_[1] & 0xF;
                imm = *((TU16 *) (_op_ + 2)); // Read 16-bit immediate value directly


; Assuming the following zero page locations for the variables
; _op_  : $04
; rs1   : $08
; rs2   : $09
; imm   : $0A

; Load _op_[1] into rs1 and rs2
    ldy #1          ; Set Y to 1 as an offset
    lda (_op_),y    ; Load the value pointed by _op_ + 1 (indirect indexed addressing)

; Calculate rs1 = _op_[1] >> 4
    pha             ; Push the loaded value onto the stack
    lsr             ; Shift right 4 bits (divide by 16)
    lsr
    lsr
    lsr
    sta rs1         ; Store the result in rs1

; Calculate rs2 = _op_[1] & 0xF
    pla             ; Pull the value from the stack
    and #$0F        ; Logical AND with 0x0F to keep the lower 4 bits
    sta rs2         ; Store the result in rs2

; Load 16-bit immediate value (imm = *((TU16 *) (_op_ + 2)))
    iny             ; Increment Y to 2
    lda (_op_),y    ; Load the value pointed by _op_ + 2 (indirect indexed addressing)
    sta imm         ; Store the lower byte of imm
    iny             ; Increment Y to 3
    lda (_op_),y    ; Load the value pointed by _op_ + 3 (indirect indexed addressing)
    sta imm+1       ; Store the higher byte of imm




                rd  = _op_[1] >> 4;
                imm = *((TU16 *) (_op_ + 2)); // Read 16-bit immediate value directly


; Assuming the following zero page locations for the variables
; _op_  : $04
; rd    : $08
; imm   : $0A

; Load _op_[1] into rd
    ldy #1          ; Set Y to 1 as an offset
    lda (_op_),y    ; Load the value pointed by _op_ + 1 (indirect indexed addressing)

; Calculate rd = _op_[1] >> 4
    lsr             ; Shift right 4 bits (divide by 16)
    lsr
    lsr
    lsr
    sta rd          ; Store the result in rd

; Load 16-bit immediate value (imm = *((TU16 *) (_op_ + 2)))
    iny             ; Increment Y to 2
    lda (_op_),y    ; Load the value pointed by _op_ + 2 (indirect indexed addressing)
    sta imm         ; Store the lower byte of imm
    iny             ; Increment Y to 3
    lda (_op_),y    ; Load the value pointed by _op_ + 3 (indirect indexed addressing)
    sta imm+1       ; Store the higher byte of imm





