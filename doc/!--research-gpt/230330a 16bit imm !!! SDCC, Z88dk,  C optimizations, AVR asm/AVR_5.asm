
; Assumptions:
;   - X register (R26 and R27) is used for indirect addressing, pointing to core.regs
;   - rd, rs1, and rs2 are already in R16, R17, and R18 respectively
;   - R19-R22 are used as temporary registers

OPR31_ADD:
    ; Calculate the addresses of core.regs[rs1] and core.regs[rs2]
    add X, R17
    ldd R19, X+
    ldd R20, X+
    ldd R21, X+
    ldd R22, X
    sub X, R17
    add X, R18
    ldd R23, X+
    ldd R24, X+
    ldd R25, X+
    ldd R26, X
    sub X, R18

    ; Perform 32-bit addition
    add R19, R23
    adc R20, R24
    adc R21, R25
    adc R22, R26

    ; Store the result in core.regs[rd]
    add X, R16
    std X+, R19
    std X+, R20
    std X+, R21
    std X, R22
    sub X, R16
    rjmp EndOfSwitch

OPR32_SUB:
    ; Calculate the addresses of core.regs[rs1] and core.regs[rs2]
    add X, R17
    ldd R19, X+
    ldd R20, X+
    ldd R21, X+
    ldd R22, X
    sub X, R17
    add X, R18
    ldd R23, X+
    ldd R24, X+
    ldd R25, X+
    ldd R26, X
    sub X, R18

    ; Perform 32-bit subtraction
    sub R19, R23
    sbc R20, R24
    sbc R21, R25
    sbc R22, R26

    ; Store the result in core.regs[rd]
    add X, R16
    std X+, R19
    std X+, R20
    std X+, R21
    std X, R22
    sub X, R16
    rjmp EndOfSwitch

OPR33_XOR:
    ; Calculate the addresses of core.regs[rs1] and core.regs[rs2]
    add X, R17
    ldd R19, X+
    ldd R20, X+
    ldd R21, X+
    ldd R22, X
    sub X, R17
    add X, R18
    ldd R23, X+
    ldd R24, X+
    ldd R25, X+
    ldd R26, X
    sub X, R18

    ; Perform 32-bit XOR
    eor R19, R23
    eor R20, R24
    eor R21, R25
    eor R22, R26

    ; Store the result in core.regs[rd]
    add X, R16
    std X+, R19
    std X+, R20
    std X+, R21
    std X, R22
    sub X, R16
    rjmp EndOfSwitch

OPR34_AND:
    ; Calculate the addresses of core.regs[rs1] and core.regs[rs2]
    add X, R17
    ldd R19, X+
    ldd R20, X+
    ldd R21, X+
    ldd R22, X
    sub X, R17
    add X, R18
    ldd R23, X+
    ldd R24, X+
    ldd R25, X+
    ldd R26, X
    sub X, R18

    ; Perform 32-bit AND
    and R19, R23
    and R20, R24
    and R21, R25
    and R22, R26

    ; Store the result in core.regs[rd]
    add X, R16
    std X+, R19
    std X+, R20
    std X+, R21
    std X, R22
    sub X, R16
    rjmp EndOfSwitch

OPR35_OR:
    ; Calculate the addresses of core.regs[rs1
