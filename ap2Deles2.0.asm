; ======== Etapa 1: Armazenar tabela ASCII em 0x200 ========
ldi ZH, 0x02        ; Parte alta do endereço inicial (0x200)
ldi ZL, 0x00        ; Parte baixa do endereço inicial

; Armazenar caracteres maiúsculos (A-Z)
ldi r16, 'A'        ; Primeiro caractere: 'A'
store_uppercase:
    st Z+, r16          ; Armazenar o caractere no endereço Z
    inc r16             ; Próximo caractere
    cpi r16, 'Z'+1      ; Verifica se passou de 'Z'
    brne store_uppercase

; Armazenar caracteres minúsculos (a-z)
ldi r16, 'a'        ; Primeiro caractere: 'a'
store_lowercase:
    st Z+, r16          ; Armazenar o caractere no endereço Z
    inc r16             ; Próximo caractere
    cpi r16, 'z'+1      ; Verifica se passou de 'z'
    brne store_lowercase

; Armazenar caracteres numéricos (0-9)
ldi r16, '0'        ; Primeiro caractere: '0'
store_digits:
    st Z+, r16          ; Armazenar o caractere no endereço Z
    inc r16             ; Próximo caractere
    cpi r16, '9'+1      ; Verifica se passou de '9'
    brne store_digits

; Armazenar espaço em branco (0x20)
ldi r16, 0x20       ; Código ASCII do espaço
st Z+, r16

; Armazenar caractere <ESC> (0x1B)
ldi r16, 0x1B       ; Código ASCII do <ESC>
st Z+, r16

; ======== Configuração da Porta de Entrada (PORTD) ========
clr r16             ; Zera r16 para configurar os pinos como entrada
out DDRD, r16       ; Configura todos os pinos de PORTD como entrada

; ======== Configuração da Porta de Saída (PORTC) ========
ldi r18, 0xFF       ; Configura todos os pinos de PORTC como saída
out DDRC, r18       ; Configura todos os pinos de PORTC como saída

; ======== Configuração inicial: apontar Z para o início da memória (0x300) ========
ldi ZH, 0x03        ; Parte alta do endereço inicial (0x300)
ldi ZL, 0x00        ; Parte baixa do endereço inicial

; ======== Inicializar o contador de caracteres ========
ldi r19, 0          ; Inicializar o contador de caracteres em 0

; ======== Loop principal para ler sequências ========
main_loop:
    ; Esperar o código inicial 0x1C
wait_for_command:
    in r16, PIND         ; Ler da porta D (PORTD)
    cpi r16, 0x1C        ; Comparar com 0x1C
    brne wait_for_command ; Se não for 0x1C, continua esperando

    ; Iniciar leitura de caracteres
read_sequence:
    in r16, PIND         ; Ler caractere da porta D (PORTD)
    
    ; Verificar se o caractere é válido (0x20 <= caractere <= 0x7E)
    cpi r16, 0x20        ; Comparar com o menor caractere válido (espaço)
    brlt read_sequence   ; Se menor que 0x20, ignorar e continuar lendo
    cpi r16, 0x7F        ; Comparar com o maior caractere válido (0x7E)
    brge read_sequence   ; Se maior que 0x7E, ignorar e continuar lendo

    ; Verificar se é o caractere <ESC> (0x1B), e se for, terminar a sequência
	in r16, PIND         ; Ler caractere da porta D (PORTD)
    cpi r16, 0x1D        ; Verificar se é <ESC>
    breq end_sequence    ; Se for, terminar a sequência

	in r16, PIND         ; Ler caractere da porta D (PORTD)
    cpi r16, 0x1B        ; Verificar se é <ESC>
    breq end_program    ; Se for, terminar a sequência

    ; Armazenar caractere na memória (0x300 a 0x400)
    st Z+, r16           ; Armazenar caractere no endereço apontado por Z

    ; Incrementar contador de caracteres
    inc r19              ; Incrementa o contador de caracteres
   ; Se for, terminar a sequência

    ; Verificar limite de memória (0x400)
    ldi r17, 0x04        ; Parte alta do limite (0x400)
    mov r18, ZH          ; Copiar o valor de ZH para r18
    cp r18, r17          ; Comparar parte alta de Z com 0x04
    brlo read_sequence   ; Se ainda dentro do limite, continuar lendo
    breq check_low       ; Se na mesma página, verificar parte baixa
    rjmp add_space       ; Se fora do limite, adicionar espaço extra e parar

check_low:
    cpi ZL, 0x00         ; Comparar parte baixa de Z com 0x00
    brlo read_sequence   ; Se dentro do limite, continuar
    rjmp add_space       ; Caso contrário, adicionar espaço extra

; Adicionar espaço extra (0x20) e parar
add_space:
    ldi r16, 0x20        ; Código ASCII do espaço
    st Z+, r16           ; Adicionar o espaço extra
    rjmp end_program     ; Encerrar programa após adicionar o espaço extra

end_sequence:
    ; Adicionar marcador de espaço (0x20) para finalizar a sequência
    ldi r16, 0x20        ; Espaço
    st Z+, r16           ; Armazenar espaço

    ; Armazenar o número de caracteres (em r19) no endereço 0x0401
    ldi ZH, 0x04         ; Parte alta do endereço de memória 0x0401
    ldi ZL, 0x01         ; Parte baixa do endereço de memória 0x0401
    mov r16, r19         ; Copiar contador para r16
    st Z+, r16           ; Armazenar o número de caracteres na memória

    ; Enviar o número de caracteres para a porta de saída (PORTC)
    out PORTC, r19       ; Enviar o valor do contador (r19) para PORTC

    ; Continuar lendo a próxima sequência
    rjmp main_loop       ; Voltar para o início do loop

end_program:
    ; Programa finalizado: loop infinito
    rjmp end_program     ; Loop infinito
