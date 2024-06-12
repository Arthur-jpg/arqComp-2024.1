;
; AssemblerApplication9.asm
;
; Created: 12/06/2024 11:08:38
; Author : Arthur
;


; Replace with your application code
ldi r16, 2
sts 0x20E, r16
ldi r16, 4
sts 0x20F, r16
ldi r16, 6
sts 0x210, r16
ldi r16, 8
sts 0x211, r16
ldi r16, 10
sts 0x212, r16
ldi r16, 12
sts 0x213, r16
ldi r16, 10
sts 0x214, r16

lds r0, 0x20E
lds r1, 0x20F
lds r2, 0x210
lds r3, 0x211
lds r4, 0x212
lds r5, 0x213
lds r6, 0x214

add r0, r1
add r0, r2
add r0, r3
add r0, r4
add r0, r5
sub r0, r6	

sts 0x215, r0
jmp 0x20

break
