;
; AssemblerApplication23.asm
;
; Created: 19/06/2024 09:26:30
; Author : Arthur
;


; Replace with your application code
ldi r16, 4
ldi r17, 3
; X
ldi r26, 0x02
ldi r27, 0x02
; Y
ldi r28, 0x03
ldi r29, 0x02


cp r16, r17
breq loop1

loop2:
sub r16, r17
st Y, r16
jmp final

loop1:
add r16, r17
st X, r16
jmp final


final:
break
