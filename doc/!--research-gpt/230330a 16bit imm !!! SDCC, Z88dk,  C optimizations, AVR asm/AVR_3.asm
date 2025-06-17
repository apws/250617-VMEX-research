
; Assumptions:
;   - Z register (R30 and R31) is used for indirect addressing, pointing to ptr
;   - R16, R17, and R18 are used as general-purpose registers for rd, rs1, and imm respectively

IE_TYPE:
; Load ptr[1] into R16 and right shift by 4 bits
ld r16, Z+1
swap r16
andi r16, 0x0F

; Load ptr[1] into R17 and mask lower 4 bits
ld r17, Z+1
andi r17, 0x0F

; Load ptr[2] and ptr[3] as a 16-bit immediate value into R18:R19
ld r18, Z+2
ld r19, Z+3

; Continue with the rest of your program (e.g., jump to the end of switch)
rjmp EndOfSwitch

