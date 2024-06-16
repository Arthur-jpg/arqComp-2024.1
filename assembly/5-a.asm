;
; AssemblerApplication20.asm
;
; Created: 16/06/2024 13:30:50
; Author : Arthur
;


; Replace with your application code
ldi r16, 0 ; inicio contador
ldi r17, 64 ; final contador
ldi r26, 0x00
ldi r27, 0x02
ldi r19, 6
st X, r19

loop:
ld r18, X
inc r16
inc r26
cp r16, r17
brne loop
break