//UNO - Receiver
//DataIn an D2 von Arduino UNO
//COM20

#include <RCSwitch.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

RCSwitch rcSwitch = RCSwitch();

LiquidCrystal_I2C lcd(0x27, 16, 2);

char homo0;
char homo1;
char homo2;
char homo3;
char homo4;
char homo5;
char homo6;
char homo7;

void setup() {
  Serial.begin(9600);
  rcSwitch.enableReceive(0); //Interrupt zum Empfangen
  pinMode(7, OUTPUT); //rot
  pinMode(6, OUTPUT); //grün
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Empfangsbereit");

  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
}

void loop() {
  if (rcSwitch.available()) {
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);

    Serial.println("Empfange...");

    homo0 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("1 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    delay(1050);

    homo1 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("2 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    delay(1000);

    homo2 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("3 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    delay(1000);

    homo3 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("4 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    delay(1000);

    homo4 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("5 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    delay(1000);

    homo5 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("6 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    delay(1000);

    homo6 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("7 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    delay(1000);

    homo7 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("8 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    Serial.print("Gesamte Ausgabe: ");
    Serial.print(homo0);
    Serial.print(", ");
    Serial.print(homo1);
    Serial.print(", ");
    Serial.print(homo2);
    Serial.print(", ");
    Serial.print(homo3);
    Serial.print(", ");
    Serial.print(homo4);
    Serial.print(", ");
    Serial.print(homo5);
    Serial.print(", ");
    Serial.print(homo6);
    Serial.print(", ");
    Serial.println(homo7);

    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);

    delay(200);

    Serial.println("Übertragung beendet");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ausgabe:");
    lcd.setCursor(0, 1);
    lcd.print(homo0);
    lcd.setCursor(1, 1);
    lcd.print(homo1);
    lcd.setCursor(2, 1);
    lcd.print(homo2);
    lcd.setCursor(3, 1);
    lcd.print(homo3);
    lcd.setCursor(4, 1);
    lcd.print(homo4);
    lcd.setCursor(5, 1);
    lcd.print(homo5);
    lcd.setCursor(6, 1);
    lcd.print(homo6);
    lcd.setCursor(7, 1);
    lcd.print(homo7);
  }
}
