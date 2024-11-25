; ======== Etapa 1: Armazenar tabela ASCII em 0x200 ========
ldi ZH, 0x02        ; Parte alta do endere�o inicial (0x200)
ldi ZL, 0x00        ; Parte baixa do endere�o inicial

; Armazenar caracteres mai�sculos (A-Z)
ldi r16, 'A'        ; Primeiro caractere: 'A'
store_uppercase:
    st Z+, r16          ; Armazenar o caractere no endere�o Z
    inc r16             ; Pr�ximo caractere
    cpi r16, 'Z'+1      ; Verifica se passou de 'Z'
    brne store_uppercase

; Armazenar caracteres min�sculos (a-z)
ldi r16, 'a'        ; Primeiro caractere: 'a'
store_lowercase:
    st Z+, r16          ; Armazenar o caractere no endere�o Z
    inc r16             ; Pr�ximo caractere
    cpi r16, 'z'+1      ; Verifica se passou de 'z'
    brne store_lowercase

; Armazenar caracteres num�ricos (0-9)
ldi r16, '0'        ; Primeiro caractere: '0'
store_digits:
    st Z+, r16          ; Armazenar o caractere no endere�o Z
    inc r16             ; Pr�ximo caractere
    cpi r16, '9'+1      ; Verifica se passou de '9'
    brne store_digits

; Armazenar espa�o em branco (0x20)
ldi r16, 0x20       ; C�digo ASCII do espa�o
st Z+, r16

; Armazenar caractere <ESC> (0x1B)
ldi r16, 0x1B       ; C�digo ASCII do <ESC>
st Z+, r16

; ======== Configura��o da Porta de Entrada (PORTD) ========
clr r16             ; Zera r16 para configurar os pinos como entrada
out DDRD, r16       ; Configura todos os pinos de PORTD como entrada

; ======== Configura��o da Porta de Sa�da (PORTC) ========
ldi r18, 0xFF       ; Configura todos os pinos de PORTC como sa�da
out DDRC, r18       ; Configura todos os pinos de PORTC como sa�da

; ======== Configura��o inicial: apontar Z para o in�cio da mem�ria (0x300) ========
ldi ZH, 0x03        ; Parte alta do endere�o inicial (0x300)
ldi ZL, 0x00        ; Parte baixa do endere�o inicial

; ======== Inicializar o contador de caracteres ========
ldi r19, 0          ; Inicializar o contador de caracteres em 0

; ======== Loop principal para ler sequ�ncias ========
main_loop:
    ; Esperar o c�digo inicial 0x1C
wait_for_command:
    in r16, PIND         ; Ler da porta D (PORTD)
    cpi r16, 0x1C        ; Comparar com 0x1C
    brne wait_for_command ; Se n�o for 0x1C, continua esperando

    ; Iniciar leitura de caracteres
read_sequence:
    in r16, PIND         ; Ler caractere da porta D (PORTD)
    
    ; Verificar se o caractere � v�lido (0x20 <= caractere <= 0x7E)
    cpi r16, 0x20        ; Comparar com o menor caractere v�lido (espa�o)
    brlt read_sequence   ; Se menor que 0x20, ignorar e continuar lendo
    cpi r16, 0x7F        ; Comparar com o maior caractere v�lido (0x7E)
    brge read_sequence   ; Se maior que 0x7E, ignorar e continuar lendo

    ; Verificar se � o caractere <ESC> (0x1B), e se for, terminar a sequ�ncia
	in r16, PIND         ; Ler caractere da porta D (PORTD)
    cpi r16, 0x1D        ; Verificar se � <ESC>
    breq end_sequence    ; Se for, terminar a sequ�ncia

	in r16, PIND         ; Ler caractere da porta D (PORTD)
    cpi r16, 0x1B        ; Verificar se � <ESC>
    breq end_program    ; Se for, terminar a sequ�ncia

    ; Armazenar caractere na mem�ria (0x300 a 0x400)
    st Z+, r16           ; Armazenar caractere no endere�o apontado por Z

    ; Incrementar contador de caracteres
    inc r19              ; Incrementa o contador de caracteres
   ; Se for, terminar a sequ�ncia

    ; Verificar limite de mem�ria (0x400)
    ldi r17, 0x04        ; Parte alta do limite (0x400)
    mov r18, ZH          ; Copiar o valor de ZH para r18
    cp r18, r17          ; Comparar parte alta de Z com 0x04
    brlo read_sequence   ; Se ainda dentro do limite, continuar lendo
    breq check_low       ; Se na mesma p�gina, verificar parte baixa
    rjmp add_space       ; Se fora do limite, adicionar espa�o extra e parar

check_low:
    cpi ZL, 0x00         ; Comparar parte baixa de Z com 0x00
    brlo read_sequence   ; Se dentro do limite, continuar
    rjmp add_space       ; Caso contr�rio, adicionar espa�o extra

; Adicionar espa�o extra (0x20) e parar
add_space:
    ldi r16, 0x20        ; C�digo ASCII do espa�o
    st Z+, r16           ; Adicionar o espa�o extra
    rjmp end_program     ; Encerrar programa ap�s adicionar o espa�o extra

end_sequence:
    ; Adicionar marcador de espa�o (0x20) para finalizar a sequ�ncia
    ldi r16, 0x20        ; Espa�o
    st Z+, r16           ; Armazenar espa�o

    ; Armazenar o n�mero de caracteres (em r19) no endere�o 0x0401
    ldi ZH, 0x04         ; Parte alta do endere�o de mem�ria 0x0401
    ldi ZL, 0x01         ; Parte baixa do endere�o de mem�ria 0x0401
    mov r16, r19         ; Copiar contador para r16
    st Z+, r16           ; Armazenar o n�mero de caracteres na mem�ria

    ; Enviar o n�mero de caracteres para a porta de sa�da (PORTC)
    out PORTC, r19       ; Enviar o valor do contador (r19) para PORTC

    ; Continuar lendo a pr�xima sequ�ncia
    rjmp main_loop       ; Voltar para o in�cio do loop

end_program:
    ; Programa finalizado: loop infinito
    rjmp end_program     ; Loop infinito
