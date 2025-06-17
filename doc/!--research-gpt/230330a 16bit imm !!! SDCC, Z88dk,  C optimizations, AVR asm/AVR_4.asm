
; Assumptions:
;   - X register (R26 and R27) is used for indirect addressing, pointing to core.regs
;   - rd, rs1, and rs2 are already in R16, R17, and R18 respectively

OPR31_ADD:
    ; Calculate the addresses of core.regs[rs1] and core.regs[rs2]
    add X, R17
    ld R19, X
    sub X, R17
    add X, R18
    ld R20, X
    sub X, R18

    ; Perform addition
    add R19, R20

    ; Store the result in core.regs[rd]
    add X, R16
    st X, R19
    sub X, R16
    rjmp EndOfSwitch

OPR32_SUB:
    ; Calculate the addresses of core.regs[rs1] and core.regs[rs2]
    add X, R17
    ld R19, X
    sub X, R17
    add X, R18
    ld R20, X
    sub X, R18

    ; Perform subtraction
    sub R19, R20

    ; Store the result in core.regs[rd]
    add X, R16
    st X, R19
    sub X, R16
    rjmp EndOfSwitch

OPR33_XOR:
    ; Calculate the addresses of core.regs[rs1] and core.regs[rs2]
    add X, R17
    ld R19, X
    sub X, R17
    add X, R18
    ld R20, X
    sub X, R18

    ; Perform XOR
    eor R19, R20

    ; Store the result in core.regs[rd]
    add X, R16
    st X, R19
    sub X, R16
    rjmp EndOfSwitch

OPR34_AND:
    ; Calculate the addresses of core.regs[rs1] and core.regs[rs2]
    add X, R17
    ld R19, X
    sub X, R17
    add X, R18
    ld R20, X
    sub X, R18

    ; Perform AND
    and R19, R20

    ; Store the result in core.regs[rd]
    add X, R16
    st X, R19
    sub X, R16
    rjmp EndOfSwitch

OPR35_OR:
    ; Calculate the addresses of core.regs[rs1] and core.regs[rs2]
    add X, R17
    ld R19, X
    sub X, R17
    add X, R18
    ld R20, X
    sub X, R18

    ; Perform OR
    or R19, R20

    ; Store the result in core.regs[rd]
    add X, R16
    st X, R19
    sub X, R16
    rjmp EndOfSwitch

EndOfSwitch:
    ; Continue with the rest of your program

