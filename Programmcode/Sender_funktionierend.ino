/* paras_näytöö
*  Oberstufenprojekt "voimala"
*  von Tom Schröter und Oliver Reichardt
*  ELGS_72
*/
//Arduino UNO - Transmitter - COM18 - Stand 28.04.2020
//Portbelegung:
//D2  - LED
//D4  - Row4
//D5  - Row3
//D6  - Row2
//D7  - Row1
//D8  - Col1
//D9  - Col2
//D10 - Col3
//D11 - Col4

#include <Keypad.h>
#include <RCSwitch.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

RCSwitch rcSwitch = RCSwitch();

const byte length_buffer = 8;

char keyBuffer [length_buffer + 1] = {'-', '-', '-', '-', '-', '-', '-', '-'};

const byte Rows = 4;
const byte Cols = 4;

long a, b, c, d, e, f, g, h;

int led = 2;

char hexaKeys [Rows] [Cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins [Rows] = {7, 6, 5, 4};
byte colPins [Cols] = {8, 9, 11, 12};

Keypad customKeypad = Keypad (makeKeymap (hexaKeys), rowPins, colPins, Rows, Cols);

void setup() {
  rcSwitch.enableTransmit(10);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Eingabe: ");

  Serial.begin(9600);
  
  pinMode(led, OUTPUT); 

  digitalWrite(led, LOW);
}

void loop() {
  char customKey = customKeypad.getKey();
  if (customKey) {
    if ((int(customKey) >= 48) && (int(customKey) <= 57) | (int(customKey) >= 65) && (int(customKey) <= 68)) {
      addToKeyBuffer(customKey);
    }
    //else if für einzelne Tastenabfragen
    else if (customKey == '#') {
      clearCode();
    }
    else if (customKey == '*') {
      output();
    }
  }
}

void addToKeyBuffer (char inkey) {
  for (int i = 1; i < length_buffer; i++) {
    keyBuffer [i - 1] = keyBuffer [i];
  }
  keyBuffer [length_buffer - 1] = inkey;
  Serial.println (keyBuffer);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Eingabe:");
  lcd.setCursor(0, 1);
  lcd.print(keyBuffer);
}

void clearCode() {
  for (int i = 0; i < length_buffer; i++) {
    keyBuffer[i] = '-';
  }
  Serial.println(keyBuffer);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Eingabe:");
  lcd.setCursor(0, 1);
  lcd.print(keyBuffer);
}

void output() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ausgabe:");
  lcd.setCursor(0, 1);
  lcd.print(keyBuffer[0]);
  lcd.setCursor(1, 1);
  lcd.print(keyBuffer[1]);
  lcd.setCursor(2, 1);
  lcd.print(keyBuffer[2]);
  lcd.setCursor(3, 1);
  lcd.print(keyBuffer[3]);
  lcd.setCursor(4, 1);
  lcd.print(keyBuffer[4]);
  lcd.setCursor(5, 1);
  lcd.print(keyBuffer[5]);
  lcd.setCursor(6, 1);
  lcd.print(keyBuffer[6]);
  lcd.setCursor(7, 1);
  lcd.print(keyBuffer[7]);

  Serial.println("Starte Übertragung...");

  digitalWrite(led, HIGH);

 // digitalWrite (3, HIGH);
  rcSwitch.send(keyBuffer[0], 24);
  Serial.print("Key: ");
  Serial.print(keyBuffer[0]);
  Serial.print(" - ");
  Serial.println(keyBuffer[0], HEX);
 // digitalWrite(3, LOW);

  delay(500);
  
 // digitalWrite (3, HIGH);
  rcSwitch.send(keyBuffer[1], 24);
  Serial.print("Key: ");
  Serial.print(keyBuffer[1]);
  Serial.print(" - ");
  Serial.println(keyBuffer[1], HEX);
 // digitalWrite(3, LOW);

  delay(500);
  
  //digitalWrite (3, HIGH);
  rcSwitch.send(keyBuffer[2], 24);
  Serial.print("Key: ");
  Serial.print(keyBuffer[2]);
  Serial.print(" - ");
  Serial.println(keyBuffer[2], HEX);
  //digitalWrite(3, LOW);

  delay(500);
  
 // digitalWrite (3, HIGH);
  rcSwitch.send(keyBuffer[3], 24);
  Serial.print("Key: ");
  Serial.print(keyBuffer[3]);
  Serial.print(" - ");
  Serial.println(keyBuffer[3], HEX);
 // digitalWrite(3, LOW);

  delay(500);

 // digitalWrite (3, HIGH);
  rcSwitch.send(keyBuffer[4], 24);
  Serial.print("Key: ");
  Serial.print(keyBuffer[4]);
  Serial.print(" - ");
  Serial.println(keyBuffer[4], HEX);
 // digitalWrite(3, LOW);

  delay(500);
  
//  digitalWrite (3, HIGH);
  rcSwitch.send(keyBuffer[5], 24);
  Serial.print("Key: ");
  Serial.print(keyBuffer[5]);
  Serial.print(" - ");
  Serial.println(keyBuffer[5], HEX);
 // digitalWrite(3, LOW);

  delay(500);
  
 // digitalWrite (3, HIGH);
  rcSwitch.send(keyBuffer[6], 24);
  Serial.print("Key: ");
  Serial.print(keyBuffer[6]);
  Serial.print(" - ");
  Serial.println(keyBuffer[6], HEX);
//  digitalWrite(3, LOW);

  delay(500);
  
 // digitalWrite (3, HIGH);
  rcSwitch.send(keyBuffer[7], 24);
  Serial.print("Key: ");
  Serial.print(keyBuffer[7]);
  Serial.print(" - ");
  Serial.println(keyBuffer[7], HEX);
 // digitalWrite(3, LOW);

  Serial.print("Gesamte Ausgabe: ");
  Serial.print(keyBuffer[0]);
  Serial.print(", ");
  Serial.print(keyBuffer[1]);
  Serial.print(", ");
  Serial.print(keyBuffer[2]);
  Serial.print(", ");
  Serial.print(keyBuffer[3]);
  Serial.print(", ");
  Serial.print(keyBuffer[4]);
  Serial.print(", ");
  Serial.print(keyBuffer[5]);
  Serial.print(", ");
  Serial.print(keyBuffer[6]);
  Serial.print(", ");
  Serial.println(keyBuffer[7]);

  digitalWrite(led, LOW);

  delay(200);
  Serial.println("Übertragung beendet");
}
