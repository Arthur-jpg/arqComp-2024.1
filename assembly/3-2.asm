;
; AssemblerApplication11.asm
;
; Created: 12/06/2024 11:33:40
; Author : Arthur
;


; Replace with your application code
ldi r16, 2
sts 0x200, r16
ldi r16, 2
sts 0x201, r16
ldi r16, 2
sts 0x202, r16
ldi r16, 2
sts 0x203, r16
ldi r16, 2
sts 0x204, r16
ldi r16, 2
sts 0x205, r16
ldi r16, 2
sts 0x206, r16

lds r0, 0x200
lds r1, 0x201
lds r2, 0x202
lds r3, 0x203
lds r4, 0x204
lds r5, 0x205
lds r6, 0x206

eor r0,r1
eor r1,r2
eor r2,r3
eor r3,r4
eor r4,r5
eor r5,r6

add r0, r1
add r0, r2
add r0, r3
add r0, r4
add r0, r5

sts 0x207, r0

	

break