;
; AssemblerApplication16.asm
;
; Created: 16/06/2024 11:49:56
; Author : Arthur
;


; Replace with your application code
ldi r16, 0 ; inicio da contagem
ldi r17, 10 ; final da contagem

loop:
inc r16
cp r16, r17
brne loop
break