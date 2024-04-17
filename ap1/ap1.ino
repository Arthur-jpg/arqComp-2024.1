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




int VAL1 = 0;


int converteDecimal(int A0, int A1, int A2, int A3, int A4){
 int decimal = 0;
 decimal = A0 + A1 * 2 + A2 * 4 + A3 * 8 + A4 * 16;
 return(decimal);
}


void setup() {
  pinMode(CH1,INPUT);
  pinMode(VED,OUTPUT);
  pinMode(VEM,OUTPUT);
  Serial.begin(9600); 


}

void loop() { 
  int a,b,c,d,e, saida;
  a = digitalRead(I4);
  b = digitalRead(I3);
  c = digitalRead(I2);
  d = digitalRead(I1);
  e = digitalRead(I0);
  saida = converteDecimal(a,b,c,d,e);
  Serial.println(saida,DEC);
  delay(6000);
  VAL1 = digitalRead(CH1);


  if (VAL1 == 0) {
    digitalWrite(VED, HIGH);
    digitalWrite(VEM, LOW);

  }

  if (VAL1 == 1) {
    digitalWrite(VEM, HIGH);
    digitalWrite(VED, LOW);
  }



}
