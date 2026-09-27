// Biblioteca bluetooth clássico
#include "BluetoothSerial.h"
// Inicializa a biblioteca do lcd I2C e DHT
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define PINO_RELE1 27
#define PINO_RELE2 12
const int PINO_TRANSISTOR = 23;
const int PINO_LDR = 34;

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(4, DHT11); 
BluetoothSerial SerialBT; 

String estadoLDR = "Lampadas OFF"; 

// Variável para controlar o tempo sem travar o Bluetooth com delay()
unsigned long tempoAnteriorDHT = 0;
const long intervaloDHT = 1000; // Atualiza DHT e LCD a cada 1 segundo

void setup() {
  Serial.begin(115200); 
  
  pinMode(PINO_TRANSISTOR, OUTPUT);
  pinMode(PINO_LDR, INPUT);
  pinMode(PINO_RELE1, OUTPUT); 
  pinMode(PINO_RELE2, OUTPUT);
  
  // Relés iniciam desligados (Relé com acionamento em nível LOW inicia em HIGH)
  digitalWrite(PINO_TRANSISTOR, LOW);
  digitalWrite(PINO_RELE1, HIGH);
  digitalWrite(PINO_RELE2, HIGH);
  
  dht.begin(); 
  SerialBT.begin("Rodando na Base da Oração"); 
  
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Sistema Iniciado");
}

void loop() {
  // 1. LEITURA DO BLUETOOTH
  if (SerialBT.available()) {
    String receberDados = SerialBT.readString();
    receberDados.trim(); // Limpa espaços e quebras de linha
    
    // Controle da Lâmpada 1 via BT
    if (receberDados == "Ligar L1") { 
      digitalWrite(PINO_RELE1, LOW); // Liga Relé 1
      estadoLDR = "L1: ON ";
    } else if (receberDados == "Desligar L1") {
      digitalWrite(PINO_RELE1, HIGH); // Desliga Relé 1
      estadoLDR = "L1: OFF";
    }

    // Controle da Lâmpada 2 via BT
    if (receberDados == "Ligar L2") {
      digitalWrite(PINO_RELE2, LOW); // Liga Relé 2
      estadoLDR = "L2: ON ";
    } else if (receberDados == "Desligar L2") {
      digitalWrite(PINO_RELE2, HIGH); // Desliga Relé 2
      estadoLDR = "L2: OFF";
    }

    // Liga/Desliga a alimentação do circuito do LDR pelo Transistor
    if (receberDados == "LIGAR_TRANSISTOR" || receberDados == "LIGAR") {
      digitalWrite(PINO_TRANSISTOR, HIGH);
    } else if (receberDados == "DESLIGAR_TRANSISTOR" || receberDados == "DESLIGAR") {
      digitalWrite(PINO_TRANSISTOR, LOW);
    }
  }

  // 2. LÓGICA DO LDR (Só atua se o Transistor estiver ativado)
  // Caso o transistor (pino 23) esteja em HIGH, permite que o LDR controle o Relé 1 automaticamente
  if (digitalRead(PINO_TRANSISTOR) == HIGH) {
    int ESTADO_LDR = digitalRead(PINO_LDR);
    
    // Ajuste aqui a lógica conforme a montagem do circuito do LDR:
    if (ESTADO_LDR == HIGH) {
      digitalWrite(PINO_RELE1, LOW);  // Liga a lâmpada no escuro
      estadoLDR = "LDR: L1 ON";
    }
  }

  // 3. LEITURA DO DHT11 E ATUALIZAÇÃO DO LCD 
  unsigned long tempoAtual = millis();
  if (tempoAtual - tempoAnteriorDHT >= intervaloDHT) {
    tempoAnteriorDHT = tempoAtual;

    float temperatura = dht.readTemperature();
    float umidade = dht.readHumidity();
    
    // Linha 0 do LCD: Umidade e Temperatura
    lcd.setCursor(0, 0);
    lcd.print("U:");
    if (isnan(umidade)) {
      lcd.print("ErrorU ");
    } else {
      lcd.print((int)umidade);
      lcd.print("% ");
    }

    lcd.print("T:");
    if (isnan(temperatura)) {
      lcd.print("ErrorT  ");
    } else {
      lcd.print((int)temperatura);
      lcd.print("C  ");
    }

    // Linha 1 do LCD: Estado atual
    lcd.setCursor(0, 1);
    lcd.print("Status: ");
    lcd.print(estadoLDR);
    lcd.print("    "); // Limpa caracteres sobressalentes
  }
}