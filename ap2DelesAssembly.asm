; ======== Etapa 1: Armazenar tabela ASCII em 0x200 ========
ldi ZH, 0x02        ; Parte alta do endere�o inicial (0x200)
ldi ZL, 0x00        ; Parte baixa do endere�o inicial

; Armazenar caracteres mai�sculos (A-Z)
ldi r16, 'A'        ; Primeiro caractere: 'A'
store_uppercase:
    st Z+, r16          ; Armazena o caractere no endere�o Z
    inc r16             ; Pr�ximo caractere
    cpi r16, 'Z'+1      ; Verifica se passou de 'Z'
    brne store_uppercase

; Armazenar caracteres min�sculos (a-z)
ldi r16, 'a'        ; Primeiro caractere: 'a'
store_lowercase:
    st Z+, r16          ; Armazena o caractere no endere�o Z
    inc r16             ; Pr�ximo caractere
    cpi r16, 'z'+1      ; Verifica se passou de 'z'
    brne store_lowercase

; Armazenar caracteres num�ricos (0-9)
ldi r16, '0'        ; Primeiro caractere: '0'
store_digits:
    st Z+, r16          ; Armazena o caractere no endere�o Z
    inc r16             ; Pr�ximo caractere
    cpi r16, '9'+1      ; Verifica se passou de '9'
    brne store_digits

; Armazenar espa�o em branco (0x20)
ldi r16, 0x20       ; C�digo ASCII do espa�o
st Z+, r16

; Armazenar caractere <ESC> (0x1B)
ldi r16, 0x1B       ; C�digo ASCII do <ESC>
st Z+, r16

; Configura��o inicial: apontar Z para o in�cio da mem�ria (0x300)
ldi ZH, 0x03        ; Parte alta do endere�o inicial (0x300)
ldi ZL, 0x00        ; Parte baixa do endere�o inicial

; Loop principal para ler sequ�ncias
main_loop:
    ; Esperar o c�digo inicial 0x1C
wait_for_command:
    in r16, PIND         ; Ler da porta D
    cpi r16, 0x1C        ; Comparar com 0x1C
    brne wait_for_command ; Se n�o for, continua esperando

    ; Iniciar leitura de caracteres
read_sequence:
    in r16, PIND         ; Ler caractere da porta D
    cpi r16, 0x1B        ; Verificar se � <ESC>
    breq end_sequence    ; Se for, terminar a sequ�ncia

    ; Validar caractere (opcional: adicionar regras de valida��o aqui)
    ; Exemplo: Aceitar apenas ASCII v�lidos entre 0x20 e 0x7E
    cpi r16, 0x20        ; Comparar com o menor caractere v�lido (espa�o)
    brlo read_sequence   ; Se menor, ignorar e ler novamente
    cpi r16, 0x7F        ; Comparar com o maior caractere v�lido
    brsh read_sequence   ; Se maior ou igual, ignorar e ler novamente

    ; Armazenar caractere na mem�ria
    st Z+, r16           ; Armazena caractere no endere�o apontado por Z

    ; Verificar limite de mem�ria (0x400)
    ldi r17, 0x04        ; Parte alta do limite (0x400)
    mov r18, ZH          ; Copiar o valor de ZH para r18
    cp r18, r17          ; Comparar parte alta de Z com 0x04
    brlo read_sequence   ; Se ainda dentro do limite, continuar lendo
    breq check_low       ; Se na mesma p�gina, verificar parte baixa
    rjmp end_program     ; Se fora do limite, terminar o programa

check_low:
    cpi ZL, 0x00         ; Comparar parte baixa de Z com 0x00
    brlo read_sequence   ; Se dentro do limite, continuar
    rjmp end_program     ; Caso contr�rio, terminar

end_sequence:
    ; Adicionar marcador de espa�o (0x20)
    ldi r16, 0x20        ; Espa�o
    st Z+, r16           ; Armazenar espa�o
    rjmp main_loop       ; Voltar para o in�cio do loop

end_program:
    ; Programa finalizado: loop infinito
    rjmp end_program
