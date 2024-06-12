;
; AssemblerApplication7.asm
;
; Created: 12/06/2024 10:55:15
; Author : Arthur
;


; Replace with your application code
ldi r16, 2
sts 0x20B, r16
ldi r16, 4
sts 0x20C, r16
lds r0, 0x20B
lds r1, 0x20C
eor r0, r1
sts 0x20D, r0
break