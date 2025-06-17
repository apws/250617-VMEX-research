
    ; Load the base address of _data_
    ldi  R26, low(_data_)
    ldi  R27, high(_data_)

    ; Load _reg_[rs1] into R20-R23
    mov  R30, R31         ; Copy the base address of _reg_ to R30 (Z-register)
    add  R30, rs1         ; Add the rs1 offset to R30 (Z-register)
    ldd  R20, Z+0         ; Load the first byte of _reg_[rs1] into R20
    ldd  R21, Z+1         ; Load the second byte of _reg_[rs1] into R21
    ldd  R22, Z+2         ; Load the third byte of _reg_[rs1] into R22
    ldd  R23, Z+3         ; Load the fourth byte of _reg_[rs1] into R23

    ; Add the immediate value to _reg_[rs1]
    ldi  R24, low(imm)    ; Load the lower 8 bits of imm into R24
    ldi  R25, high(imm)   ; Load the upper 8 bits of imm into R25
    add  R20, R24         ; Add the lower 8 bits of the immediate value
    adc  R21, R25         ; Add the upper 8 bits of the immediate value and carry
    adc  R22, R1          ; Add carry (R1 is assumed to be cleared beforehand)
    adc  R23, R1          ; Add carry (R1 is assumed to be cleared beforehand)

    ; Add the result to the base address of _data_
    add  R26, R20
    adc  R27, R21

    ; Load the 32-bit word from memory
    ld   R16, X+0         ; Load the first byte of the memory location into R16
    ld   R17, X+1         ; Load the second byte of the memory location into R17
    ld   R18, X+2         ; Load the third byte of the memory location into R18
    ld   R19, X+3         ; Load the fourth byte of the memory location into R19

    ; Store the loaded word into _reg_[rd]
    mov  R30, R31         ; Copy the base address of _reg_ to R30 (Z-register)
    add  R30, rd          ; Add the rd offset to R30 (Z-register)
    st   Z+0, R16         ; Store the first byte of the result
    st   Z+1, R17         ; Store the second byte of the result
    st   Z+2, R18         ; Store the third byte of the result
    st   Z+3, R19         ; Store the fourth byte of the result

