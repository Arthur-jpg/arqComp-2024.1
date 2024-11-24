; ======== Etapa 1: Armazenar tabela ASCII em 0x200 ========
ldi ZH, 0x02        ; Parte alta do endereço inicial (0x200)
ldi ZL, 0x00        ; Parte baixa do endereço inicial

; Armazenar caracteres maiúsculos (A-Z)
ldi r16, 'A'        ; Primeiro caractere: 'A'
store_uppercase:
    st Z+, r16          ; Armazena o caractere no endereço Z
    inc r16             ; Próximo caractere
    cpi r16, 'Z'+1      ; Verifica se passou de 'Z'
    brne store_uppercase

; Armazenar caracteres minúsculos (a-z)
ldi r16, 'a'        ; Primeiro caractere: 'a'
store_lowercase:
    st Z+, r16          ; Armazena o caractere no endereço Z
    inc r16             ; Próximo caractere
    cpi r16, 'z'+1      ; Verifica se passou de 'z'
    brne store_lowercase

; Armazenar caracteres numéricos (0-9)
ldi r16, '0'        ; Primeiro caractere: '0'
store_digits:
    st Z+, r16          ; Armazena o caractere no endereço Z
    inc r16             ; Próximo caractere
    cpi r16, '9'+1      ; Verifica se passou de '9'
    brne store_digits

; Armazenar espaço em branco (0x20)
ldi r16, 0x20       ; Código ASCII do espaço
st Z+, r16

; Armazenar caractere <ESC> (0x1B)
ldi r16, 0x1B       ; Código ASCII do <ESC>
st Z+, r16

; Configuração inicial: apontar Z para o início da memória (0x300)
ldi ZH, 0x03        ; Parte alta do endereço inicial (0x300)
ldi ZL, 0x00        ; Parte baixa do endereço inicial

; Loop principal para ler sequências
main_loop:
    ; Esperar o código inicial 0x1C
wait_for_command:
    in r16, PIND         ; Ler da porta D
    cpi r16, 0x1C        ; Comparar com 0x1C
    brne wait_for_command ; Se não for, continua esperando

    ; Iniciar leitura de caracteres
read_sequence:
    in r16, PIND         ; Ler caractere da porta D
    cpi r16, 0x1B        ; Verificar se é <ESC>
    breq end_sequence    ; Se for, terminar a sequência

    ; Validar caractere (opcional: adicionar regras de validação aqui)
    ; Exemplo: Aceitar apenas ASCII válidos entre 0x20 e 0x7E
    cpi r16, 0x20        ; Comparar com o menor caractere válido (espaço)
    brlo read_sequence   ; Se menor, ignorar e ler novamente
    cpi r16, 0x7F        ; Comparar com o maior caractere válido
    brsh read_sequence   ; Se maior ou igual, ignorar e ler novamente

    ; Armazenar caractere na memória
    st Z+, r16           ; Armazena caractere no endereço apontado por Z

    ; Verificar limite de memória (0x400)
    ldi r17, 0x04        ; Parte alta do limite (0x400)
    mov r18, ZH          ; Copiar o valor de ZH para r18
    cp r18, r17          ; Comparar parte alta de Z com 0x04
    brlo read_sequence   ; Se ainda dentro do limite, continuar lendo
    breq check_low       ; Se na mesma página, verificar parte baixa
    rjmp end_program     ; Se fora do limite, terminar o programa

check_low:
    cpi ZL, 0x00         ; Comparar parte baixa de Z com 0x00
    brlo read_sequence   ; Se dentro do limite, continuar
    rjmp end_program     ; Caso contrário, terminar

end_sequence:
    ; Adicionar marcador de espaço (0x20)
    ldi r16, 0x20        ; Espaço
    st Z+, r16           ; Armazenar espaço
    rjmp main_loop       ; Voltar para o início do loop

end_program:
    ; Programa finalizado: loop infinito
    rjmp end_program
