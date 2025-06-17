
; Assumptions:
;   - Z register (R30 and R31) is used for indirect addressing, pointing to ptr
;   - R16, R17, and R18 are used as general-purpose registers for rd, rs1, and rs2 respectively

RD_TYPE:
; Load ptr[1] into R16 and right shift by 4 bits
ld r16, Z+1
swap r16
andi r16, 0x0F

; Load ptr[2] into R17 and right shift by 4 bits
ld r17, Z+2
swap r17
andi r17, 0x0F

; Load ptr[3] into R18 and right shift by 4 bits
ld r18, Z+3
swap r18
andi r18, 0x0F

; Continue with the rest of your program (e.g., jump to the end of switch)
rjmp EndOfSwitch

