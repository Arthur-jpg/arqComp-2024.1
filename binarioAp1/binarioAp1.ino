// Defina as portas onde as chaves estão conectadas
const int chave1Pin = 51;
const int chave2Pin = 49;
const int chave3Pin = 47;
const int chave4Pin = 45;
const int chave5Pin = 43;

void setup() {
  // Configure as portas das chaves como entrada
  pinMode(chave1Pin, INPUT);
  pinMode(chave2Pin, INPUT);
  pinMode(chave3Pin, INPUT);
  pinMode(chave4Pin, INPUT);
  pinMode(chave5Pin, INPUT);

}

void loop() {
  // Leitura do estado das chaves
  int chave1 = digitalRead(chave1Pin);
  int chave2 = digitalRead(chave2Pin);
  int chave3 = digitalRead(chave3Pin);
  int chave4 = digitalRead(chave4Pin);
  int chave5 = digitalRead(chave5Pin);

  // Concatena os estados das chaves em uma string binária
  String binario = String(chave1) + String(chave2) + String(chave3) + String(chave4) + String(chave5);

  // Converte a string binária para um número inteiro
  int numero = binario.toInt();

  // Imprime o número binário e decimal na porta serial
  // Serial.print("Binário: ");
  // Serial.print(binario);
  // Serial.print(", Decimal: ");
  // Serial.println(numero);

  Serial.print(binario);

  
}
