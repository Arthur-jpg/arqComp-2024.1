// Definir os leds
#define LED1 4
#define LED2 5
#define LED3 6
#define LED4 3
#define LED5 2
#define LED6 7

int VAL1 = 0;
int VAL2 = 0;
int VAL3 = 0;
int VAL4 = 0;
int VAL5 = 0;


// Definir as chaves
#define CH1 8
#define CH2 9
#define CH5 10
#define CH6 12
#define CH7 13






void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(CH1,INPUT);
  pinMode(LED2,OUTPUT);
  pinMode(CH2,INPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(LED6,OUTPUT);
  pinMode(CH5,INPUT);
  pinMode(CH6,INPUT);
  pinMode(CH7,INPUT);
 

}

void loop() {

  VAL1 = digitalRead(CH1);
  VAL2 = digitalRead(CH2);
  VAL3 = digitalRead(CH5);
  VAL4 = digitalRead(CH6);
  VAL5 = digitalRead(CH7);



  if((VAL1==0) && (VAL2 == 0) && (VAL3 == 1)) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  } 
  else if ((VAL1 == 0) && (VAL2==1) && (VAL3 == 1)) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
  }  
  else if((VAL1==1) && (VAL2==1) && (VAL3 == 1)) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
  }  
  else {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW); 
  }






   if((VAL4==0) && (VAL5 == 0) && (VAL3 == 0)) {
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, HIGH);
    digitalWrite(LED6, LOW);
  } 
  else if ((VAL4 == 1) && (VAL5==0) && (VAL3 == 0)) {
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, HIGH);
  }  
  else if((VAL4==1) && (VAL5==1) && (VAL3 == 0)) {
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, HIGH);
    digitalWrite(LED6, HIGH);
  }  
  else {
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW); 
  }

  
delay(1000);



}
