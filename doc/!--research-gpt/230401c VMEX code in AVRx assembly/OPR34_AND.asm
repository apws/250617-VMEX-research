
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
    ldd  R21, X+1         ; Load the second byte of _reg_[rs2] into R21
    ldd  R22, X+2         ; Load the third byte of _reg_[rs2] into R22
    ldd  R23, X+3         ; Load the fourth byte of _reg_[rs2] into R23

    ; Perform bitwise AND
    and  R16, R20         ; AND the first bytes
    and  R17, R21         ; AND the second bytes
    and  R18, R22         ; AND the third bytes
    and  R19, R23         ; AND the fourth bytes

    ; Store the result in _reg_[rd]
    mov  R26, R31         ; Copy the base address of _reg_ to R26 (X-register)
    add  R26, rd          ; Add the rd offset to R26 (X-register)
    st   X+0, R16         ; Store the first byte of the result
    st   X+1, R17         ; Store the second byte of the result
    st   X+2, R18         ; Store the third byte of the result
    st   X+3, R19         ; Store the fourth byte of the result

