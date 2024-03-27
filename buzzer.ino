#define S0 2
#define S1 3
#define S2 4

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  tone(S0, 50, 100); // Gera um tom de 50 Hz, no pino S0, com duração de 100 milissegundos
  delay(2000); // Atraso de 2000 milissegundos
  tone(S1, 1000, 300); // Gera um tom de 1 kHz, no pino S1, com duração de 300 milissegundos
  delay(2000); // Atraso de 2000 milissegundos
  tone(S2, 2000, 500); // Gera um tom de 2 kHz, no pino S2, com duração de 500 milissegundos
  delay(2000);
}
