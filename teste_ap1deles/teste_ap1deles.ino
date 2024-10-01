#include <Ultrasonic.h>

// Definições dos pinos e variáveis de controle
#define BIN1 46
#define BIN2 48
#define BIN3 50
#define BIN4 52

#define TRIGGER_PIN 10
#define ECHO_PIN 11

#define LEDA 5
#define LEDB 6
#define LEDC 7

#define BUZZ 2

#define trig 22
#define echo 24

#define sensorPresenca 8

bool isProgramActive = false;
int modoAtual = 0;

bool medirDistancia = false;  // Variável para controlar a execução contínua da medição de distância
bool detectarMov = false;     // Variável para controlar a execução contínua do sensor de movimento

double distancia = 0;

int VAL1 = 0;
int VAL2 = 0;
int VAL3 = 0;
int VAL4 = 0;
int valorSensor = 0;

// Função para desligar todos os componentes e resetar variáveis
void desligarTudo() {
    digitalWrite(LEDA, LOW);
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDC, LOW);
    digitalWrite(BUZZ, LOW);
    medirDistancia = false;  // Desativa medição de distância quando o programa é encerrado
    detectarMov = false;     // Desativa detecção de movimento quando o programa é encerrado
    modoAtual = 0;           // Reseta o modo atual
    isProgramActive = false;
    Serial.println("Todos os componentes foram desligados.");
}

// Função para medir a distância usando sensor ultrassônico
void distancias() {
    if (modoAtual == 3) {  // Executa apenas se a medição de distância estiver ativa
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        distancia = pulseIn(echo, HIGH);
        distancia = distancia * 340;
        distancia = distancia / 2;
        distancia = distancia / 10000;
        Serial.print("Distância medida: ");
        Serial.println(distancia);
        delay(500);  // Adiciona um pequeno delay para evitar leitura muito rápida
    }
}

// Função para detectar movimento
void detectarMovimento() {
    if (modoAtual == 4) {  // Executa apenas se a detecção de movimento estiver ativa
        valorSensor = digitalRead(sensorPresenca);
        if (valorSensor == HIGH) {
            Serial.println("TEM GENTE");
        } else {
            Serial.println("NÃO TEM GENTE");
        }
        delay(500);  // Adiciona um pequeno delay para evitar leitura muito rápida
    }
}

// Função para processar comandos recebidos via monitor serial
void serialTeste() {
    if (Serial.available() > 0) {
        String comando = Serial.readStringUntil('\n');  // Lê a linha de comando até nova linha
        comando.trim();  // Remove espaços em branco extras

        if (comando == "FIM_PROG") {
            Serial.println("Programação desativada via comando serial.");
            desligarTudo();  // Desliga tudo e encerra a programação
        } else if (comando == "DIST_CHECKA") {
            Serial.println("Medição de distância ativada.");
            desligarTudo();  // Desativa qualquer função ativa antes de ativar a medição de distância
            medirDistancia = true;
            modoAtual = 3;   // Define modo para medição de distância
        } else if (comando == "DIST_STOP") {
            Serial.println("Medição de distância desativada.");
            desligarTudo();  // Desativa a medição de distância
        } else if (comando == "PRES_READA") {
            Serial.println("Detecção de movimento ativada.");
            desligarTudo();  // Desativa qualquer função ativa antes de ativar a detecção de movimento
            detectarMov = true;
            modoAtual = 4;   // Define modo para detecção de movimento
        } else if (comando == "PRES_STOP") {
            Serial.println("Detecção de movimento desativada.");
            desligarTudo();  // Desativa a detecção de movimento
        }
    }
}

// Função para processar comandos recebidos via binário
void binarioTeste() {
    if (VAL1 == 1 && VAL2 == 0 && VAL3 == 1 && VAL4 == 1) {
        Serial.println("Programação encerrada");
        desligarTudo();  // Encerra e reseta todas as funcionalidades
    }

    if (isProgramActive) {
        if ((VAL1 == 0) && (VAL2 == 0) && (VAL3 == 0) && (VAL4 == 0)) {
            Serial.println("Acendendo LED A.");
            digitalWrite(LEDA, HIGH);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
        } else if ((VAL1 == 1) && (VAL2 == 0) && (VAL3 == 0) && (VAL4 == 0)) {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
        } else if ((VAL1 == 1) && (VAL2 == 1) && (VAL3 == 1) && (VAL4 == 0)) {
            Serial.println("Medição de distância ativada via configuração binária.");
            medirDistancia = true;
            modoAtual = 3;   // Define modo para medição de distância
        } else if ((VAL1 == 0) && (VAL2 == 0) && (VAL3 == 0) && (VAL4 == 1)) {
            Serial.println("Detecção de movimento ativada via configuração binária.");
            detectarMov = true;
            modoAtual = 4;   // Define modo para detecção de movimento
        }
    }
}

// Configuração inicial do Arduino
void setup() {
    pinMode(BIN1, INPUT);
    pinMode(BIN2, INPUT);
    pinMode(BIN3, INPUT);
    pinMode(BIN4, INPUT);
    pinMode(LEDA, OUTPUT);
    pinMode(BUZZ, OUTPUT);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(sensorPresenca, INPUT);
  
    Serial.begin(9600);
    Serial.println("Digite os comandos no formato: 'comando'");
    Serial.println("Comandos disponíveis:");
    Serial.println(" - ativar: INICIO_PROG");
    Serial.println(" - desativar: FIM_PROG");
}

// Loop principal do programa
void loop() {
    // Lê os valores das entradas binárias
    VAL1 = digitalRead(BIN1);
    VAL2 = digitalRead(BIN2);
    VAL3 = digitalRead(BIN3);
    VAL4 = digitalRead(BIN4);

    delay(500);

    // Verifica se o programa está no estado inicial e aguarda comandos para ativar
    if (modoAtual == 0) {
        if (Serial.available() > 0) {
            String comando = Serial.readStringUntil('\n');
            comando.trim();
            if (comando == "INICIO_PROG") {
                Serial.println("Programação ativada via comando serial.");
                modoAtual = 1;
                isProgramActive = true;
            }
        }
        if (VAL1 == 0 && VAL2 == 0 && VAL3 == 1 && VAL4 == 1) {
            Serial.println("Programação ativada via configuração binária.");
            isProgramActive = true;
            modoAtual = 2;
        }
    }

    // Verifica o modo atual e executa a função correspondente
    if (modoAtual == 1) {
        serialTeste();  // Checa comandos e executa continuamente
    } else if (modoAtual == 2) {
        binarioTeste();  // Checa e executa com base nos valores binários
    } else if (modoAtual == 3) {
        distancias();  // Executa medição de distância continuamente
    } else if (modoAtual == 4) {
        detectarMovimento();  // Executa detecção de movimento continuamente
    }
}
