#include "BluetoothSerial.h"
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

// Limiares de luz ambiente (ajustável)
const int LIMIAR_ESCURO = 1000; // Valor com a lanterna cobrindo (ajustado para ser mais sensível)
const int LIMIAR_CLARO = 2200;  // Valor com luz da lanterna 

bool cobertoPeloDedo = false;
String estadoLCD = "Modo: Automatico";

void setup() {
  Serial.begin(115200); 
  
  pinMode(PINO_LDR, INPUT);
  
  // O transistor liga no setup e NUNCA mais desliga a alimentação do LDR
  pinMode(PINO_TRANSISTOR, OUTPUT);
  digitalWrite(PINO_TRANSISTOR, HIGH); 

  pinMode(PINO_RELE1, OUTPUT); 
  pinMode(PINO_RELE2, OUTPUT);
  // Inicia relés desligados (Assumindo relés acionados em LOW)
  digitalWrite(PINO_RELE1, HIGH); 
  digitalWrite(PINO_RELE2, HIGH);

  dht.begin(); 
  SerialBT.begin("Rodando na Base da Oração"); 
  
  lcd.init(); 
  lcd.backlight();
}

void loop() {
  // -------------------------------------------------------------
  // 1. LEITURA AUTOMÁTICA DO LDR
  // -------------------------------------------------------------
  int leituraLDR = analogRead(PINO_LDR);
  
  // Valor da luminosidade no monitor serial
  Serial.print("Leitura LDR: ");
  Serial.println(leituraLDR);

  // SE COLOCAR a Lanterna do celular: Liga ambas as lâmpadas imediatamente
  if (leituraLDR < LIMIAR_ESCURO && !cobertoPeloDedo) {
    digitalWrite(PINO_RELE1, LOW);
    digitalWrite(PINO_RELE2, LOW);
    cobertoPeloDedo = true;
    estadoLCD = "LDR: Dedo (L1+L2)";
  } 
  // SE TIRAR a Lanterna do celular: Desliga as lâmpadas e volta ao normal
  else if (leituraLDR > LIMIAR_CLARO && cobertoPeloDedo) {
    digitalWrite(PINO_RELE1, HIGH);
    digitalWrite(PINO_RELE2, HIGH);
    cobertoPeloDedo = false;
    estadoLCD = "LDR: Livre";
  }

  // -------------------------------------------------------------
  // 2. COMANDOS VIA BLUETOOTH
  // -------------------------------------------------------------
  if (SerialBT.available()) {
    String receberDados = SerialBT.readString();
    receberDados.trim();
    
    if (receberDados == "Ligar L1") {
      digitalWrite(PINO_RELE1, LOW);
      estadoLCD = "BT: L1 ON";
    } 
    else if (receberDados == "Desligar L1") { 
      digitalWrite(PINO_RELE1, HIGH);
      estadoLCD = "BT: L1 OFF";
    }
    else if (receberDados == "Ligar L2") {
      digitalWrite(PINO_RELE2, LOW);
      estadoLCD = "BT: L2 ON";
    } 
    else if (receberDados == "Desligar L2") {
      digitalWrite(PINO_RELE2, HIGH);
      estadoLCD = "BT: L2 OFF";
    }
  }

  // -------------------------------------------------------------
  // 3. LEITURA DO DHT11 E EXIBIÇÃO NO LCD
  // -------------------------------------------------------------
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  
  // Linha 0: Umidade e Temperatura
  lcd.setCursor(0, 0);
  lcd.print("U:");
  if (isnan(umidade)) {
    lcd.print("Err ");
  } else {
    lcd.print((int)umidade);
    lcd.print("% ");
  }

  lcd.print("T:");
  if (isnan(temperatura)) {
    lcd.print("Err ");
  } else {
    lcd.print((int)temperatura);
    lcd.print("C  ");
  }

  // Linha 1: Status no LCD
  lcd.setCursor(0, 1);
  lcd.print("                "); // Limpa a linha
  lcd.setCursor(0, 1);
  lcd.print(estadoLCD);

  delay(150); // Leitura ultra-rápida (150 milissegundos)
}