#include <stdio.h>
#include <stdio.h>
#include <string.h>
#define CH1 2
#define VED 3
#define VEM 4

#define I0 51
#define I1 49
#define I2 47
#define I3 45
#define I4 43

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

#define LED1 15
#define LED2 16
#define LED3 17
#define LED4 18
#define LED5 19

#define LED6 11
#define CHT 10

#define B1 5




int VAL1 = 0;
int VAL2 = 0;
int hora_entrada  = 0;
int hora_saida = 0;
int data_atua = 0;
int hora = 15;
int conta = 0;

int converteDecimal(int A0, int A1, int A2, int A3, int A4){
 int decimal = 0;
 decimal = A0 + A1 * 2 + A2 * 4 + A3 * 8 + A4 * 16;
 return(decimal);
}


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


}

void loop() {
  VAL1 = digitalRead(CH1); 
  VAL2 = digitalRead(CHT);
  
  hora = hora;
  hora_entrada = readDipSwitchentrada();
  hora_saida = readDipSwitchsaida();
  data_atua = readDataAtual();
  

  if (hora > 24) {
    activate_leds();

  } else {
    Serial.println(hora_entrada,DEC);
    Serial.println(hora_saida,DEC);

    if (VAL1 == 0) {
      digitalWrite(VED, LOW);
      digitalWrite(VEM, HIGH);

    }

    if (VAL1 == 1) {
      digitalWrite(VEM, LOW);
      digitalWrite(VED, HIGH);
      if (VAL2 == 1) {
        digitalWrite(LED6, HIGH);
        tone(B1,2500,50000); 
        delay(10);
      } else {
        digitalWrite(LED6,LOW);
        noTone(B1); 
        delay(10);
      }
      



    }
  }
  delay(1000);
}

int readDipSwitchentrada() {
  int a,b,c,d,e, entrada_decimal;
  a = digitalRead(I4);
  b = digitalRead(I3);
  c = digitalRead(I2);
  d = digitalRead(I1);
  e = digitalRead(I0);
  entrada_decimal = converteDecimal(a,b,c,d,e);


  if (entrada_decimal > 23){
    return 0;
  }
  else {
    return entrada_decimal;
  }





}

int readDipSwitchsaida() {
  int f,g,h,i,j, saida;
  f = digitalRead(T0);
  g = digitalRead(T1);
  h = digitalRead(T2);
  i = digitalRead(T3);
  j = digitalRead(T4);
  saida = converteDecimal(f,g,h,i,j);
 
  if (saida > 23){
    return 0;
  }
  else {
    return saida;
  }


}

float readDataAtual() {
  hora_entrada = readDipSwitchentrada();
  hora_saida = readDipSwitchsaida();
  hora = hora;

  if (hora < hora_entrada || hora > hora_saida) {
    return 0;
  } else {
    int conta = hora_saida - hora;
    Serial.println(conta,DEC);
    return conta;

  }

}


// Função para ativar LEDs
void activate_leds() {
    // Piscar todos os LEDs cinco vezes
    for (int i = 0; i < 5; i++) {
        // Ligar todos os LEDs
        for (int led = 1; led <= 5; led++) {
          digitalWrite(LED1, HIGH);
          digitalWrite(LED2, HIGH);
          digitalWrite(LED3, HIGH);
          digitalWrite(LED4, HIGH);
          digitalWrite(LED5, HIGH);
        }
        // Aguardar um curto período de tempo
        delay(500); // Por exemplo, meio segundo
        // Desligar todos os LEDs
        for (int led = 1; led <= 5; led++) {
          digitalWrite(LED1, LOW);
          digitalWrite(LED2, LOW);
          digitalWrite(LED3, LOW);
          digitalWrite(LED4, LOW);
          digitalWrite(LED5, LOW);
        }
        // Aguardar um curto período de tempo
        delay(500); // Por exemplo, meio segundo
    }
}








