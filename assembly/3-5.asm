;
; AssemblerApplication15.asm
;
; Created: 15/06/2024 13:22:09
; Author : Arthur
;


; Replace with your application code

; CP -> comprara o valor armazenado em dois registradores
; BREQ -> Desvia para o endereço se os operandos forem iguais
; BRNE -> desvia o endereço se os operandos forem diferentes
; ST -> armazena dados em endereço de memória definido em X(r27, r26)

ldi r16, 0 ; vai ser o contador
ldi r17, 10 ; armazena o valor final do loop
ldi r18, 2 ; armazena o valor inicial
ldi r19, 2 ; armazena o valor do incremento par

mov r20,r18 ; r20: soma dos pares 

loop: ; rótulo de loop
add r18,r19 ; soma o valor inicial com o incremento par
add r20,r18 ; armazena a soma dos valores
inc r16 ; incrementa contador
cp r17,r16 ; compara contador com flag se o contador for igual ao flag o brne não vai retormar ao loop
brne loop

break