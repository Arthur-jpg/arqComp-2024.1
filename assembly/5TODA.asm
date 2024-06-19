;
; AssemblerApplication24.asm
;
; Created: 19/06/2024 09:34:47
; Author : Arthur
;


; Replace with your application code
ldi r16, 0 ; contador
ldi r17, 64 ; final do contador
ldi r20, 0 ; contador de número menor que 50

ldi r26, 0x00 
ldi r27, 0x02

ldi r19, 50

.MACRO teste
ld r18, X
cpi r18, r19
brlo conta
jmp fim
conta: inc r20
fim:
.ENDMACRO


loop1:
ld r18, X
teste
inc r26
inc r16
cp r16, r17
brne loop1
break

inc r26
st X, r20
break