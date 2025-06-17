//NOT SURE IF THIS SI REALLY CORRECT
//WE CAN PROBABLY ALSO OMIT THE STORING RS1 TO STACK AS HIS VALUE IS NEVER CHANGED IN OPERATION AND CAN BE INDEXED
//BOTH SOURCE REGISTERS rsN are INTACT during entire operation and result it stored in rd register


; Assuming the following zero page locations for the variables
; rd    : $08
; rs1   : $09
; rs2   : $0A
; _reg_ : $0C
; shift : $0E

; Calculate _reg_[rs1] address
    lda rs1
    asl             ; Multiply by 4 (shift left by 2)
    asl
    tay             ; Use Y as an index for _reg_[rs1]

; Calculate _reg_[rs2] address
    lda rs2
    asl             ; Multiply by 4 (shift left by 2)
    asl
    tax             ; Use X as an index for _reg_[rs2]

; Get shift count (_reg_[rs2] & 0x1F)
    lda _reg_,x
    and #0x1F
    sta shift

; Calculate _reg_[rd] address
    lda rd
    asl             ; Multiply by 4 (shift left by 2)
    asl
    tay             ; Use Y as an index for _reg_[rd]

; Perform the 32-bit logical shift left
    ldx #0
LShiftLoop:
    cpx shift       ; Check if all bits are shifted
    beq Done
    lda _reg_,y     ; Load the lowest byte of _reg_[rs1]
    rol             ; Rotate left
    sta _reg_,y     ; Store back the result
    iny
    lda _reg_,y     ; Load the next byte of _reg_[rs1]
    rol             ; Rotate left
    sta _reg_,y     ; Store back the result
    iny
    lda _reg_,y     ; Load the next byte of _reg_[rs1]
    rol             ; Rotate left
    sta _reg_,y     ; Store back the result
    iny
    lda _reg_,y     ; Load the highest byte of _reg_[rs1]
    rol             ; Rotate left
    sta _reg_,y     ; Store back the result
    tya             ; Transfer Y to A
    sec             ; Set carry flag
    sbc #3          ; Subtract 3 to return to the lowest byte
    tay             ; Transfer A to Y
    dex             ; Decrement X
    jmp LShiftLoop  ; Jump to LShiftLoop
Done:





//WELL ITS NOT CORRECT BUT WE CAN START HERE

; Assuming the following zero page locations for the variables
; rd    : $08
; rs1   : $09
; rs2   : $0A
; _reg_ : $0C
; shift : $0E

; Calculate _reg_[rs1] address
    lda rs1
    asl             ; Multiply by 4 (shift left by 2)
    asl
    tay             ; Use Y as an index for _reg_[rs1]

; Calculate _reg_[rs2] address
    lda rs2
    asl             ; Multiply by 4 (shift left by 2)
    asl
    tax             ; Use X as an index for _reg_[rs2]

; Get shift count (_reg_[rs2] & 0x1F)
    lda _reg_,x
    and #0x1F
    sta shift

; Calculate _reg_[rd] address
    lda rd
    asl             ; Multiply by 4 (shift left by 2)
    asl
    tay             ; Use Y as an index for _reg_[rd]

; Perform the 32-bit logical shift left
    ldx #0
LShiftLoop:
    cpx shift       ; Check if all bits are shifted
    beq Done
    ldy rs1         ; Load the lowest byte of _reg_[rs1]
    lda _reg_,y
    rol             ; Rotate left
    sta _reg_,y     ; Store the result in _reg_[rd]
    iny
    ldy rs1+1       ; Load the next byte of _reg_[rs1]
    lda _reg_,y
    rol             ; Rotate left
    sta _reg_,y     ; Store the result in _reg_[rd]
    iny
    ldy rs1+2       ; Load the next byte of _reg_[rs1]
    lda _reg_,y
    rol             ; Rotate left
    sta _reg_,y     ; Store the result in _reg_[rd]
    iny
    ldy rs1+3       ; Load the highest byte of _reg_[rs1]
    lda _reg_,y
    rol             ; Rotate left
    sta _reg_,y     ; Store the result in _reg_[rd]
    tya             ; Transfer Y to A
    sec             ; Set carry flag
    sbc #3          ; Subtract 3 to return to the lowest byte
    tay             ; Transfer A to Y
    dex             ; Decrement X
    jmp LShiftLoop  ; Jump to LShiftLoop
Done:


