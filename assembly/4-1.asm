;
; AssemblerApplication18.asm
;
; Created: 16/06/2024 12:34:12
; Author : Arthur
;


; Replace with your application code
ldi r16, 0 ; zerar contador
ldi r17, 20 ; final do contador
ldi r18, 99 ; valor incial
ldi r19, 2 ; para subir de impar a impar
ldi r26, 0x00
ldi r27, 0x02

loop1:
add r18, r19
st X, r18
inc r16
inc r26
cp r16, r17
brne loop1

break

ldi r16, 0
ldi r17, 20
ldi r26, 0x00
ldi r27, 0x02

loop2:
ld r19, X
dec r19
st y, r19
inc r16
inc r26
inc r28
cp r16, r17
brne loop2

break

