;
; AssemblerApplication10.asm
;
; Created: 12/06/2024 11:27:17
; Author : Arthur
;


; Replace with your application code
ldi r16, 2
sts 0x200, r16
ldi r16, 4
sts 0x201, r16
ldi r16, 6
sts 0x202, r16
ldi r16, 8
sts 0x203, r16
ldi r16, 10
sts 0x204, r16
ldi r16, 12
sts 0x205, r16
ldi r16, 14
sts 0x206, r16

lds r0, 0x200
lds r1, 0x201
lds r2, 0x202
lds r3, 0x203
lds r4, 0x204
lds r5, 0x205
lds r6, 0x206

add r0, r1
add r0, r2
add r0, r3
add r0, r4
add r0, r5
add r0, r6

sts 0x207, r0
break
