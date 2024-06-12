;
; AssemblerApplication5.asm
;
; Created: 11/06/2024 11:38:01
; Author : Arthur
;


; Replace with your application code
ldi r16, 52
sts 0x200, r16
ldi r17, 54
sts 0x201, r17
ldi r18, 56
sts 0x202, r18
ldi r19, 58
sts 0x203, r19
ldi r20, 60
sts 0x204, r20
ldi r21, 62
sts 0x205, r21
ldi r22, 64
sts 0x206, r22
ldi r23, 66
sts 0x207, r23
ldi r24, 68
sts 0x208, r24
ldi r25, 70
sts 0x209, r25
ldi r26, 72
sts 0x20A, r26

lds r0, 0x200
lds r1, 0x201
add r0, r1
lds r1, 0x202
add r0, r1
lds r1, 0x203
add r0, r1
lds r1, 0x204
add r0, r1
lds r1, 0x205
add r0, r1
lds r1, 0x206
add r0, r1
lds r1, 0x207
add r0, r1
lds r1, 0x208
add r0, r1
lds r1, 0x209
add r0, r1
lds r1, 0x20A
add r0, r1
sts 0x20B, r0
break