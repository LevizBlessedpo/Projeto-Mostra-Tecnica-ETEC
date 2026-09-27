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

// Variável global para manter o estado da lâmpada visível no loop
String estadoLDR = "Desconhecido"; 

void setup() {
  Serial.begin(115200); 
  pinMode(PINO_TRANSISTOR, OUTPUT);
  pinMode(PINO_LDR, INPUT);
  pinMode(PINO_RELE1, OUTPUT); 
  pinMode(PINO_RELE2, OUTPUT);
  digitalWrite(PINO_TRANSISTOR, LOW);
  digitalWrite(PINO_RELE1, HIGH);
  digitalWrite(PINO_RELE2, HIGH);
  dht.begin(); 
  SerialBT.begin("Rodando na Base da Oração"); 
  lcd.init(); 
  lcd.backlight();
}

void loop() {
  String receberDados = "";
  int ESTADO_LDR = digitalRead(PINO_LDR);
  
  // Leitura do Bluetooth
  if (SerialBT.available()) {
    receberDados = SerialBT.readString();
    receberDados.trim();
    
    // Controle da lâmpada 1
    if (receberDados == "Desligar L1") {
      digitalWrite(PINO_RELE1, HIGH); 
      estadoLDR = "Lampada OFF";
    } else if (receberDados == "Ligar L1") { 
      digitalWrite(PINO_RELE1, LOW);
      estadoLDR = "Lampada ON";
    }

    // Controle da lâmpada 2
    if (receberDados == "Desligar L2") {
      digitalWrite(PINO_RELE2, HIGH);
      estadoLDR = "Lampada OFF";
    } else if (receberDados == "Ligar L2") {
      digitalWrite(PINO_RELE2, LOW);
      estadoLDR = "Lampada ON";
    }

    if(receberDados == "LIGAR") {
      digitalWrite(PINO_TRANSISTOR, HIGH);
    } else if (receberDados == "DESLIGAR") {
      digitalWrite(PINO_TRANSISTOR, LOW);
    }
  }

  if (ESTADO_LDR == HIGH) {
    digitalWrite(PINO_RELE, HIGH); // Acende a lâmpada
  } else {
    digitalWrite(PINO_RELE, LOW);  // Apaga a lâmpada
  }

  // Leitura do sensor DHT11
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  
  // Atualiza a primeira linha do LCD (Temperatura)
  lcd.setCursor(0, 0);
  // Umidade no lcd
  lcd.print("U: ");
  if(isnan(umidade)) {
    lcd.print ("ErroU   ");
  } else {
    lcd.print(umidade, 1);
    lcd.print("%");
  }

  // Temperatura no lcd
  lcd.print("T: ");
  if (isnan(temperatura)) {
    lcd.print("ErroT    ");
  } else {
    lcd.print(temperatura, 1);
    lcd.print("C");
  }

  // Atualiza a segunda linha do LCD (Estado da lâmpada)
  lcd.setCursor(0, 1);
  lcd.print("                "); // Limpa a linha para evitar sobreposição de textos antigos
  lcd.setCursor(0, 1);
  lcd.print(estadoLDR);

  delay(1000); // Aumentado para 1 segundo para dar tempo de leitura estável do DHT11
}