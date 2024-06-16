;
; AssemblerApplication19.asm
;
; Created: 16/06/2024 13:19:50
; Author : Arthur
;


; Replace with your application code
ldi r16, 101
ldi r17, 101

cp r16, r17
breq soma
jmp diferenca

soma:
add r16, r17
ldi r26, 0x02
ldi r27, 0x02
st X, r16
jmp final

diferenca:
sub r16,r17
ldi r26, 0x03
ldi r25, 0x02
st X, r16
jmp final

final:
break

