#include <stdio.h>
#include <string.h>

#define CH1 2
#define VED 3
#define VEM 4

#define I0 52
#define I1 50
#define I2 48
#define I3 46
#define I4 44

#define T0 41
#define T1 39
#define T2 37
#define T3 35
#define T4 33

#define S0 9
#define S1 10
#define S2 11
#define S3 12
#define S4 13

#define LED1 19
#define LED2 18
#define LED3 17
#define LED4 16
#define LED5 15

#define LED6 11
#define CHT 10

#define B1 5

//definições de variáveis globais

int hora = 0;
int minuto = 0;
int segundo = 0;
int entrada = 0;
int saida = 0;
int calculo = 0;
int VAL1 = 0;
int VAL2 = 0;

// setup das chaves e dos leds como output e input
void setup() {
  pinMode(CH1,INPUT);
  pinMode(VED,OUTPUT);
  pinMode(VEM,OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(CHT, INPUT);
  pinMode(B1,OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  Serial.begin(9600); 
  
  // Printar no serial monitor no início da aplicação
  Serial.println("Entre a hora atual: ");
}

// função para converter binario em decimal
int converteDecimal(int A0, int A1, int A2, int A3, int A4){
 int decimal = 0;
 decimal = A0 + A1 * 2 + A2 * 4 + A3 * 8 + A4 * 16;
 return(decimal);
}

// Função para incrementar o segundo
void incrementaSegundo() {
  segundo++;
  if (segundo >= 60) {
    segundo = 0;
    minuto++;
    if (minuto >= 60) {
      minuto = 0;
      hora++;
      if (hora >= 24) {
        hora = 0;
      }
    }
  }
}

// Função para exibir a hora formatada no monitor serial
void printHora() {
  Serial.print("Hora: ");
  if (hora < 10) Serial.print("0");
  Serial.print(hora);
  Serial.print(":");
  if (minuto < 10) Serial.print("0");
  Serial.print(minuto);
  Serial.print(":");
  if (segundo < 10) Serial.print("0");
  Serial.println(segundo);
}

// função para fazer o complemento de 1
void activate_countdown_leds(int complemento) {
    // Para garantir que o complemento vai ser positivo
    if (complemento < 0) {
        complemento = -complemento;
    }

    // Exibir o complemento de 1 nos LEDs
    digitalWrite(LED1, complemento & 0x01);
    digitalWrite(LED2, complemento & 0x02);
    digitalWrite(LED3, complemento & 0x04);
    digitalWrite(LED4, complemento & 0x08);
    digitalWrite(LED5, complemento & 0x10);

}

int binarioParaDecimal() {
  int a, b, c, d, e, f, g, h, i, j;
  a = digitalRead(I4);
  b = digitalRead(I3);
  c = digitalRead(I2);
  d = digitalRead(I1);
  e = digitalRead(I0);
  f = digitalRead(T4);
  g = digitalRead(T3);
  h = digitalRead(T2);
  i = digitalRead(T1);
  j = digitalRead(T0);

  entrada = converteDecimal(a, b, c, d, e);
  // Serial.println(entrada);
  saida = converteDecimal(f, g, h, i, j);
  // Serial.println(saida);
  calculo = saida - hora;
  // Serial.println(calculo);
  return calculo;
}

void ledsLow() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
}
void ledsHigh() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
}

void detectarMovimento() {
  if (VAL2 == 1) {
    digitalWrite(LED6, HIGH);
    tone(B1,2500,50000); 
    delay(10);
  } else if (VAL2 == 0){
    noTone(B1);
    digitalWrite(LED6,LOW);
  } else {
    noTone(B1);
    digitalWrite(LED6,LOW);
  }
}

void naoDedectarMovimento() {
    if (VAL2 == 1) {
    noTone(B1);
    digitalWrite(LED6,LOW);
  } else if (VAL2 == 0){
    noTone(B1);
    digitalWrite(LED6,LOW);
  }
}

void ifGeral() {
    if (VAL1 == 1) {
    digitalWrite(VEM, LOW);
    digitalWrite(VED, HIGH);
  }  else if (VAL1 == 0) {
    digitalWrite(VEM, HIGH);
    digitalWrite(VED, LOW);
  }
}

void loop() {
  // Se houver dados disponíveis no monitor serial
  VAL1 = digitalRead(CH1); 
  if (VAL1 == 1) {
    digitalWrite(VEM, LOW);
    digitalWrite(VED, HIGH);
  } else if (VAL1 == 0) {
    digitalWrite(VEM, HIGH);
    digitalWrite(VED, LOW);
  }

  if (Serial.available() > 0) {
    // Lê os dados inseridos pelo usuário
    hora = Serial.parseInt();
    minuto = Serial.parseInt();
    
    // Limpa o buffer do serial
    while (Serial.available() > 0) {

      Serial.read();
    }

    // Verifica se os valores inseridos são válidos
    if (hora >= 0 && hora <= 23 && minuto >= 0 && minuto <= 59 && segundo >= 0 && segundo <= 59) {
      // Exibe a hora formatada no monitor serial
      Serial.println("Hora atual:");
      printHora();

      
      // Entra no modo relógio
      while (true) {
        delay(1000); // Aguarda um segundo
        incrementaSegundo(); // Incrementa o segundo
        printHora(); // Exibe a hora formatada

        VAL1 = digitalRead(CH1); 
        VAL2 = digitalRead(CHT);
        calculo = binarioParaDecimal();

        int complement = ~calculo + 1; // Calcula o complemento de 1 do tempo restante
        activate_countdown_leds(complement);

        if (hora > saida || hora < entrada || calculo < 1 ){
          Serial.print("Horário alarme desativado!");
          ledsLow();
          ifGeral();
          break;
        } else {
          if (VAL1 == 1) {
            digitalWrite(VEM, LOW);
            digitalWrite(VED, HIGH);
            detectarMovimento();
          } else if (VAL1 == 0) {
            digitalWrite(VEM, HIGH);
            digitalWrite(VED, LOW);
            ledsLow();
            naoDedectarMovimento();
            Serial.println("alarme desativado");
            break;
          }
        }
        
      }
    } else {
      // Se os valores inseridos não forem válidos, exibe uma mensagem de erro
      Serial.println("Valores de hora inválidos. Por favor, insira valores válidos (HH MM SS):");
      for (int i = 0; i < 5; i++) {
          // Ligar todos os LEDs
        for (int led = 1; led <= 5; led++) {
          ledsHigh();
        }
        // Aguardar um curto período de tempo
        delay(500); 
        // Desligar todos os LEDs
        for (int led = 1; led <= 5; led++) {
          ledsLow();
        }
        // Aguardar um curto período de tempo
        delay(500); // Por exemplo, meio segundo
      }
    }
  }
}

