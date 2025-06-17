
    ; Load the first operand from _reg_[rs1]
    mov  R26, R31         ; Copy the base address of _reg_ to R26 (X-register)
    add  R26, rs1         ; Add the rs1 offset to R26 (X-register)
    ldd  R16, X+0         ; Load the first byte of _reg_[rs1] into R16
    ldd  R17, X+1         ; Load the second byte of _reg_[rs1] into R17
    ldd  R18, X+2         ; Load the third byte of _reg_[rs1] into R18
    ldd  R19, X+3         ; Load the fourth byte of _reg_[rs1] into R19

    ; Load the second operand from _reg_[rs2]
    mov  R26, R31         ; Copy the base address of _reg_ to R26 (X-register)
    add  R26, rs2         ; Add the rs2 offset to R26 (X-register)
    ldd  R20, X+0         ; Load the first byte of _reg_[rs2] into R20

    ; Calculate the shift amount
    andi R20, 0x1F        ; AND with 0x1F to get the lower 5 bits

    ; Perform 32-bit left shift
ShiftLoop:
    sbrc R20, 0           ; Test the least significant bit of R20
    rjmp ShiftByte        ; If the bit is set, perform a byte shift
    rjmp ShiftBit         ; If the bit is clear, perform a bit shift

ShiftByte:
    mov  R16, R17         ; Shift bytes
    mov  R17, R18
    mov  R18, R19
    clr  R19
    subi R20, 8           ; Subtract 8 from the shift count
    rjmp ShiftLoop

ShiftBit:
    rol  R16              ; Perform bit shift with carry
    rol  R17
    rol  R18
    rol  R19
    dec  R20              ; Decrement the shift count
    brne ShiftLoop        ; Repeat the loop until the shift count reaches 0

    ; Store the result in _reg_[rd]
    mov  R26, R31         ; Copy the base address of _reg_ to R26 (X-register)
    add  R26, rd          ; Add the rd offset to R26 (X-register)
    st   X+0, R16         ; Store the first byte of the result
    st   X+1, R17         ; Store the second byte of the result
    st   X+2, R18         ; Store the third byte of the result
    st   X+3, R19         ; Store the fourth byte of the result

