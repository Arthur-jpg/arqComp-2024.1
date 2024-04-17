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

#define LED5 11
#define CHT 10

#define B1 5



int VAL1 = 0;
int VAL2 = 0;

int converteDecimal(int A0, int A1, int A2, int A3, int A4){
 int decimal = 0;
 decimal = A0 + A1 * 2 + A2 * 4 + A3 * 8 + A4 * 16;
 return(decimal);
}


void setup() {
  pinMode(CH1,INPUT);
  pinMode(VED,OUTPUT);
  pinMode(VEM,OUTPUT);
  pinMode(LED5, OUTPUT);
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
  int a,b,c,d,e, entrada;
  a = digitalRead(I4);
  b = digitalRead(I3);
  c = digitalRead(I2);
  d = digitalRead(I1);
  e = digitalRead(I0);
  entrada = converteDecimal(a,b,c,d,e);
  Serial.println(entrada,DEC);
  delay(1000);
  VAL1 = digitalRead(CH1);

  int f,g,h,i,j, saida;
  f = digitalRead(T0);
  g = digitalRead(T1);
  h = digitalRead(T2);
  i = digitalRead(T3);
  j = digitalRead(T4);
  saida = converteDecimal(f,g,h,i,j);
  Serial.println(saida,DEC);
  delay(1000);

  

  VAL2 = digitalRead(CHT);


  if (VAL1 == 0) {
    digitalWrite(VED, HIGH);
    digitalWrite(VEM, LOW);

  }

  if (VAL1 == 1) {
    digitalWrite(VEM, HIGH);
    digitalWrite(VED, LOW);
    if (VAL2 == 1) {
      digitalWrite(LED5, HIGH);
      // tone(B1,2500,50000); 
      // delay(10);
    } else {
      digitalWrite(LED5,LOW);
    }
    



  }




}
