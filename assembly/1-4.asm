;
; AssemblerApplication4.asm
;
; Created: 11/06/2024 11:27:58
; Author : Arthur
;
; Armazenar os valores do registrador r5 na mem�ria posi��o 0x200


; Replace with your application code
ldi r16, 2
mov r0, r16
ldi r16, 4
mov r1, r16
ldi r16, 6
mov r2, r16
ldi r16, 8
mov r3, r16
ldi r16, 10
mov r4, r16
ldi r16, 12
mov r5, r16
add r5, r0
add r5, r1
add r5, r2
add r5, r3
add r5, r4
sts 0x200, r5
break
