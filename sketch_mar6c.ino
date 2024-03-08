// Definir os leds
#define LED1 4
#define LED2 5
#define LED3 6
int VAL1 = 0;
int VAL2 = 0;

// Definir as chaves
#define CH1 8
#define CH2 9




void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(CH1,INPUT);
  pinMode(LED2,OUTPUT);
  pinMode(CH2,INPUT);
  pinMode(LED3,OUTPUT);
}

void loop() {

  VAL1 = digitalRead(CH1);
  VAL2 = digitalRead(CH2);

  if((VAL1==0) && (VAL2 == 0)) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  } 
  else if ((VAL1 == 0) && (VAL2==1)) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
  }  
  else if((VAL1==1) && (VAL2==1)) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
  }  
  else {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW); 
  }
delay(1000);



}
