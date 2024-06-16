;
; AssemblerApplication17.asm
;
; Created: 16/06/2024 12:03:06
; Author : Arthur
;


; Replace with your application code
ldi r16, 0 ; inicio da contagem
ldi r17, 10; final da contagem
ldi r18, 0 ; número inicial
ldi r19, 2 ; aumento dos números pares
ldi r26, 0x00 ; carrega o 0x00 de 0x0200
ldi r27, 0x02 ; carrega o 0x02 de 0x 0200

mov r20, r18 ; o registrador r20 vai ficar com a soma dos números

loop:
add r18, r19 ; add o número inicial com o somador de par
st x, r18 ; armazena o dado de r18 no endereço definido por X
add r20, r18 ; vai acumular o valor no r20
inc r16 ; incrementar 1 na contagem
inc r26 ; incrementar 1 no endereço de memória
cp r17, r16
brne loop

sts 0x20A, r20 ; vai armazenar o r20 (acumulador) no endereço 0x20A

break
