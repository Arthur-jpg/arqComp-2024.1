void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  
  // Insira aqui o número binário que deseja converter
  long long numero_binario = 1010;
  
  int decimal = binario_para_decimal(numero_binario);
  
  Serial.print("O número decimal equivalente é: ");
  Serial.println(decimal); // Imprime o número decimal na porta serial
}

void loop() {
  // O loop não é necessário para este exemplo
}

// Função para converter número binário para decimal
int binario_para_decimal(long long binario) {
    int decimal = 0, expoente = 0;
    
    // Iterar sobre cada dígito binário, da direita para a esquerda
    while (binario != 0) {
        int digito = binario % 10; // Pega o último dígito
        decimal += digito * pow(2, expoente); // Adiciona o dígito multiplicado pela potência de 2 ao resultado
        binario /= 10; // Remove o último dígito
        expoente++; // Aumenta o expoente
    }
    
    Serial.println(decimal);
    return decimal;
}

