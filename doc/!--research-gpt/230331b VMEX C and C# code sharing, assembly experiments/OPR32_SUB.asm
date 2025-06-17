
; Assuming the following zero page locations for the variables
; rd : $08
; rs1 : $09
; rs2 : $0A
; reg : $0C

; Calculate reg[rs1] address
lda rs1
asl ; Multiply by 4 (shift left by 2)
asl
tay ; Use Y as an index for reg[rs1]

; Push reg[rs1] onto the stack
lda reg,y
pha
iny
lda reg,y
pha
iny
lda reg,y
pha
iny
lda reg,y
pha

; Calculate reg[rs2] address
lda rs2
asl ; Multiply by 4 (shift left by 2)
asl
tax ; Use X as an index for reg[rs2]

; Calculate reg[rd] address
lda rd
asl ; Multiply by 4 (shift left by 2)
asl
tay ; Use Y as an index for reg[rd]

; Subtract reg[rs2] from reg[rs1] and store the result in reg[rd]
ldx #0 ; Reset X for iterating through 32-bit values
pla
sec
sbc reg,x
sta reg,y
inx
iny
pla
sbc reg,x
sta reg,y
inx
iny
pla
sbc reg,x
sta reg,y
inx
iny
pla
sbc reg,x
sta reg,y
