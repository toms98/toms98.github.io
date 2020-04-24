//Oberstufenprojekt - Arduino UNO - Receiver - COM20
//Portbelegung:
//D2 - DataIn 433Mhz
//D6 - LED grün
//D7 - LED rot
//D8 - SH3
//D9 - ST3
//D10 - Data3
//D11 - SH2
//D12 - ST2
//D13 - Data2

#include <RCSwitch.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

RCSwitch rcSwitch = RCSwitch();

LiquidCrystal_I2C lcd(0x27, 16, 2);

//Variablen
char digit1, digit2, digit3, digit4,
     digit5, digit6, digit7, digit8;

long holder = B1000000;
long mask = B11111111;
long row1  = 32768; //B1000000000000000;
long row2  = 16384; //B0100000000000000;
long row3  = 8192;  //B0010000000000000;
long row4  = 4096;  //B0001000000000000;
long row5  = 2048;  //B0000100000000000;
long row6  = 1024;  //B0000010000000000;
long row7  = 512;   //B0000001000000000;
long row8  = 256;   //B0000000100000000;
long row9  = 128;   //B0000000010000000;
long row10 = 64;    //B0000000001000000;
long row11 = 32;    //B0000000000100000;
long row12 = 16;    //B0000000000010000;
long row13 = 8;     //B0000000000001000;
long row14 = 4;     //B0000000000000100;
long row15 = 2;     //B0000000000000010;

int dataPin2 = 8;   //DS - Pin 14
int latchPin2 = 9;  //ST - Pin 13
int clockPin2 = 10; //SH - Pin 12
int dataPin3 = 11;  //DS - Pin 14
int latchPin3 = 12; //ST - Pin 13
int clockPin3 = 13; //SH - Pin 12

/* ----------------------------------------------*/
/* ------------- d = digit, r = row -------------*/
/* ---------------- 1 | 2 | 3 | 4 ---------------*/
/* ---------------- 5 | 6 | 7 | 8 ---------------*/
/* ----------------------------------------------*/
long d1r1, d1r2, d1r3, d1r4, d1r5, d1r6, d1r7, d1r8,
     d2r1, d2r2, d2r3, d2r4, d2r5, d2r6, d2r7, d2r8,
     d3r1, d3r2, d3r3, d3r4, d3r5, d3r6, d3r7, d3r8,
     d4r1, d4r2, d4r3, d4r4, d4r5, d4r6, d4r7, d4r8,
     d5r1, d5r2, d5r3, d5r4, d5r5, d5r6, d5r7, d6r1,
     d6r2, d6r3, d6r4, d6r5, d6r6, d6r7, d7r1, d7r2,
     d7r3, d7r4, d7r5, d7r6, d7r7, d8r1, d8r2, d8r3,
     d8r4, d8r5, d8r6, d8r7,   r1,   r2,   r3,   r4,
     r5,     r6,   r7,   r8,   r9, rr10, rr11, rr12,
     rr13, rr14, rr15, col1, col2, colH, col3, rowA,
     rowB;

//Arrays
/* 6er Array */
int sixArray [33] = {  0,  2,  4,  6,  8, 10, 12, 14,
                       16, 18, 20, 22, 24, 26, 28, 30,
                       32, 34, 36, 38, 40, 42, 44, 46,
                       48, 50, 52, 54, 56, 58, 60, 62
                    };
/*
  000000, 000010, 000100, 000110, 001000, 001010, 001100, 001110,
  010000, 010010, 010100, 010110, 011000, 011010, 011100, 011110,
  100000, 100010, 100100, 100110, 101000, 101010, 101100, 101110,
  110000, 110010, 110100, 110110, 111000, 111010, 111100, 111110
*/
/* 5er Array */
int endArray [33] = {    1,  3,  5,  7,  9, 11, 13, 15,
                         17, 19, 21, 23, 25, 27, 29, 31,
                         33, 35, 37, 39, 41, 43, 45, 47,
                         49, 51, 53, 55, 57, 59, 61, 63
                    };
/*
  000001, 000011, 000101, 000111, 001001, 001011, 001101, 001111,
  010001, 010011, 010101, 010111, 011001, 011011, 011101, 011111,
  100001, 100011, 100101, 100111, 101001, 101011, 101101, 101111,
  110001, 110011, 110101, 110111, 111001, 111011, 111101, 111111
*/
//endArray überall mit 1 am Ende - bei shiftOut mit LSB
//wird die Zahl so nicht gekürzt

void setup() {
  Serial.begin(9600);
  rcSwitch.enableReceive(0); //Interrupt zum Empfangen
  pinMode(6, OUTPUT); //grün
  pinMode(7, OUTPUT); //rot
  pinMode(clockPin3, OUTPUT);
  pinMode(latchPin3, OUTPUT);
  pinMode(dataPin3, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);

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
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Empfange...");

    digit1 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("1 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    delay(1050);

    digit2 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("2 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    delay(1000);

    digit3 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("3 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    delay(1000);

    digit4 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("4 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    delay(1000);

    digit5 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("5 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    delay(1000);

    digit6 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("6 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    delay(1000);

    digit7 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("7 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    delay(1000);

    digit8 = rcSwitch.getReceivedValue();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] - ");
    Serial.print("8 - ");
    Serial.println(rcSwitch.getReceivedValue(), HEX);
    rcSwitch.resetAvailable();

    Serial.print("Gesamte Ausgabe: ");
    Serial.print(digit1);
    Serial.print(", ");
    Serial.print(digit2);
    Serial.print(", ");
    Serial.print(digit3);
    Serial.print(", ");
    Serial.print(digit4);
    Serial.print(", ");
    Serial.print(digit5);
    Serial.print(", ");
    Serial.print(digit6);
    Serial.print(", ");
    Serial.print(digit7);
    Serial.print(", ");
    Serial.println(digit8);

    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);

    delay(200);

    Serial.println("Übertragung beendet");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ausgabe:");
    lcd.setCursor(0, 1);
    lcd.print(digit1);
    lcd.setCursor(1, 1);
    lcd.print(digit2);
    lcd.setCursor(2, 1);
    lcd.print(digit3);
    lcd.setCursor(3, 1);
    lcd.print(digit4);
    lcd.setCursor(4, 1);
    lcd.print(digit5);
    lcd.setCursor(5, 1);
    lcd.print(digit6);
    lcd.setCursor(6, 1);
    lcd.print(digit7);
    lcd.setCursor(7, 1);
    lcd.print(digit8);

    /* if - Abfragen des Grauens */
    //digit1
    if (digit1 == '0') {
      d1r1 = sixArray[14];
      d1r2 = sixArray[17];
      d1r3 = sixArray[19];
      d1r4 = sixArray[21];
      d1r5 = sixArray[25];
      d1r6 = sixArray[17];
      d1r7 = sixArray[14];
      d1r8 = sixArray[0];
    }
    if (digit1 == '1') {
      d1r1 = sixArray[4];
      d1r2 = sixArray[12];
      d1r3 = sixArray[4];
      d1r4 = sixArray[4];
      d1r5 = sixArray[4];
      d1r6 = sixArray[4];
      d1r7 = sixArray[14];
      d1r8 = sixArray[0];
    }
    if (digit1 == '2') {
      d1r1 = sixArray[14];
      d1r2 = sixArray[17];
      d1r3 = sixArray[1];
      d1r4 = sixArray[2];
      d1r5 = sixArray[4];
      d1r6 = sixArray[8];
      d1r7 = sixArray[31];
      d1r8 = sixArray[0];
    }
    if (digit1 == '3') {
      d1r1 = sixArray[14];
      d1r2 = sixArray[17];
      d1r3 = sixArray[1];
      d1r4 = sixArray[2];
      d1r5 = sixArray[1];
      d1r6 = sixArray[17];
      d1r7 = sixArray[14];
      d1r8 = sixArray[0];
    }
    if (digit1 == '4') {
      d1r1 = sixArray[2];
      d1r2 = sixArray[6];
      d1r3 = sixArray[10];
      d1r4 = sixArray[31];
      d1r5 = sixArray[2];
      d1r6 = sixArray[2];
      d1r7 = sixArray[2];
      d1r8 = sixArray[0];
    }
    if (digit1 == '5') {
      d1r1 = sixArray[31];
      d1r2 = sixArray[16];
      d1r3 = sixArray[16];
      d1r4 = sixArray[30];
      d1r5 = sixArray[1];
      d1r6 = sixArray[17];
      d1r7 = sixArray[14];
      d1r8 = sixArray[0];
    }
    if (digit1 == '6') {
      d1r1 = sixArray[6];
      d1r2 = sixArray[8];
      d1r3 = sixArray[16];
      d1r4 = sixArray[30];
      d1r5 = sixArray[17];
      d1r6 = sixArray[17];
      d1r7 = sixArray[14];
      d1r8 = sixArray[0];
    }
    if (digit1 == '7') {
      d1r1 = sixArray[31];
      d1r2 = sixArray[17];
      d1r3 = sixArray[2];
      d1r4 = sixArray[4];
      d1r5 = sixArray[4];
      d1r6 = sixArray[4];
      d1r7 = sixArray[4];
      d1r8 = sixArray[0];
    }
    if (digit1 == '8') {
      d1r1 = sixArray[14];
      d1r2 = sixArray[17];
      d1r3 = sixArray[17];
      d1r4 = sixArray[14];
      d1r5 = sixArray[17];
      d1r6 = sixArray[17];
      d1r7 = sixArray[14];
      d1r8 = sixArray[0];
    }
    if (digit1 == '9') {
      d1r1 = sixArray[14];
      d1r2 = sixArray[17];
      d1r3 = sixArray[17];
      d1r4 = sixArray[15];
      d1r5 = sixArray[1];
      d1r6 = sixArray[2];
      d1r7 = sixArray[12];
      d1r8 = sixArray[0];
    }
    if (digit1 == 'A') {
      d1r1 = sixArray[14];
      d1r2 = sixArray[17];
      d1r3 = sixArray[17];
      d1r4 = sixArray[17];
      d1r5 = sixArray[31];
      d1r6 = sixArray[17];
      d1r7 = sixArray[17];
      d1r8 = sixArray[0];
    }
    if (digit1 == 'B') {
      d1r1 = sixArray[30];
      d1r2 = sixArray[17];
      d1r3 = sixArray[17];
      d1r4 = sixArray[30];
      d1r5 = sixArray[17];
      d1r6 = sixArray[17];
      d1r7 = sixArray[30];
      d1r8 = sixArray[0];
    }
    if (digit1 == 'C') {
      d1r1 = sixArray[14];
      d1r2 = sixArray[17];
      d1r3 = sixArray[16];
      d1r4 = sixArray[16];
      d1r5 = sixArray[16];
      d1r6 = sixArray[17];
      d1r7 = sixArray[14];
      d1r8 = sixArray[0];
    }
    if (digit1 == 'D') {
      d1r1 = sixArray[28];
      d1r2 = sixArray[18];
      d1r3 = sixArray[17];
      d1r4 = sixArray[17];
      d1r5 = sixArray[17];
      d1r6 = sixArray[18];
      d1r7 = sixArray[28];
      d1r8 = sixArray[0];
    }
    if (digit1 == '-') {
      d1r1 = sixArray[0];
      d1r2 = sixArray[0];
      d1r3 = sixArray[0];
      d1r4 = sixArray[0];
      d1r5 = sixArray[0];
      d1r6 = sixArray[0];
      d1r7 = sixArray[0];
      d1r8 = sixArray[0];
    }

    //digit2
    if (digit2 == '0') {
      d2r1 = sixArray[14];
      d2r2 = sixArray[17];
      d2r3 = sixArray[19];
      d2r4 = sixArray[21];
      d2r5 = sixArray[25];
      d2r6 = sixArray[17];
      d2r7 = sixArray[14];
      d2r8 = sixArray[0];
    }
    if (digit2 == '1') {
      d2r1 = sixArray[4];
      d2r2 = sixArray[12];
      d2r3 = sixArray[4];
      d2r4 = sixArray[4];
      d2r5 = sixArray[4];
      d2r6 = sixArray[4];
      d2r7 = sixArray[14];
      d2r8 = sixArray[0];

    }
    if (digit2 == '2') {
      d2r1 = sixArray[14];
      d2r2 = sixArray[17];
      d2r3 = sixArray[1];
      d2r4 = sixArray[2];
      d2r5 = sixArray[4];
      d2r6 = sixArray[8];
      d2r7 = sixArray[31];
      d2r8 = sixArray[0];
    }
    if (digit2 == '3') {
      d2r1 = sixArray[14];
      d2r2 = sixArray[17];
      d2r3 = sixArray[1];
      d2r4 = sixArray[2];
      d2r5 = sixArray[1];
      d2r6 = sixArray[17];
      d2r7 = sixArray[14];
      d2r8 = sixArray[0];
    }
    if (digit2 == '4') {
      d2r1 = sixArray[2];
      d2r2 = sixArray[6];
      d2r3 = sixArray[10];
      d2r4 = sixArray[31];
      d2r5 = sixArray[2];
      d2r6 = sixArray[2];
      d2r7 = sixArray[2];
      d2r8 = sixArray[0];
    }
    if (digit2 == '5') {
      d2r1 = sixArray[31];
      d2r2 = sixArray[16];
      d2r3 = sixArray[16];
      d2r4 = sixArray[30];
      d2r5 = sixArray[1];
      d2r6 = sixArray[17];
      d2r7 = sixArray[14];
      d2r8 = sixArray[0];
    }
    if (digit2 == '6') {
      d2r1 = sixArray[6];
      d2r2 = sixArray[8];
      d2r3 = sixArray[16];
      d2r4 = sixArray[30];
      d2r5 = sixArray[17];
      d2r6 = sixArray[17];
      d2r7 = sixArray[14];
      d2r8 = sixArray[0];
    }
    if (digit2 == '7') {
      d2r1 = sixArray[31];
      d2r2 = sixArray[17];
      d2r3 = sixArray[2];
      d2r4 = sixArray[4];
      d2r5 = sixArray[4];
      d2r6 = sixArray[4];
      d2r7 = sixArray[4];
      d2r8 = sixArray[0];
    }
    if (digit2 == '8') {
      d2r1 = sixArray[14];
      d2r2 = sixArray[17];
      d2r3 = sixArray[17];
      d2r4 = sixArray[14];
      d2r5 = sixArray[17];
      d2r6 = sixArray[17];
      d2r7 = sixArray[14];
      d2r8 = sixArray[0];
    }
    if (digit2 == '9') {
      d2r1 = sixArray[14];
      d2r2 = sixArray[17];
      d2r3 = sixArray[17];
      d2r4 = sixArray[15];
      d2r5 = sixArray[1];
      d2r6 = sixArray[2];
      d2r7 = sixArray[12];
      d2r8 = sixArray[0];
    }
    if (digit2 == 'A') {
      d2r1 = sixArray[14];
      d2r2 = sixArray[17];
      d2r3 = sixArray[17];
      d2r4 = sixArray[17];
      d2r5 = sixArray[31];
      d2r6 = sixArray[17];
      d2r7 = sixArray[17];
      d2r8 = sixArray[0];
    }
    if (digit2 == 'B') {
      d2r1 = sixArray[30];
      d2r2 = sixArray[17];
      d2r3 = sixArray[17];
      d2r4 = sixArray[30];
      d2r5 = sixArray[17];
      d2r6 = sixArray[17];
      d2r7 = sixArray[30];
      d2r8 = sixArray[0];
    }
    if (digit2 == 'C') {
      d2r1 = sixArray[14];
      d2r2 = sixArray[17];
      d2r3 = sixArray[16];
      d2r4 = sixArray[16];
      d2r5 = sixArray[16];
      d2r6 = sixArray[17];
      d2r7 = sixArray[14];
      d2r8 = sixArray[0];
    }
    if (digit2 == 'D') {
      d2r1 = sixArray[28];
      d2r2 = sixArray[18];
      d2r3 = sixArray[17];
      d2r4 = sixArray[17];
      d2r5 = sixArray[17];
      d2r6 = sixArray[18];
      d2r7 = sixArray[28];
      d2r8 = sixArray[0];
    }
    if (digit2 == '-') {
      d2r1 = sixArray[0];
      d2r2 = sixArray[0];
      d2r3 = sixArray[0];
      d2r4 = sixArray[0];
      d2r5 = sixArray[0];
      d2r6 = sixArray[0];
      d2r7 = sixArray[0];
      d2r8 = sixArray[0];
    }

    //digit3
    if (digit3 == '0') {
      d3r1 = sixArray[14];
      d3r2 = sixArray[17];
      d3r3 = sixArray[19];
      d3r4 = sixArray[21];
      d3r5 = sixArray[25];
      d3r6 = sixArray[17];
      d3r7 = sixArray[14];
      d3r8 = sixArray[0];
    }
    if (digit3 == '1') {
      d3r1 = sixArray[4];
      d3r2 = sixArray[12];
      d3r3 = sixArray[4];
      d3r4 = sixArray[4];
      d3r5 = sixArray[4];
      d3r6 = sixArray[4];
      d3r7 = sixArray[14];
      d3r8 = sixArray[0];
    }
    if (digit3 == '2') {
      d3r1 = sixArray[14];
      d3r2 = sixArray[17];
      d3r3 = sixArray[1];
      d3r4 = sixArray[2];
      d3r5 = sixArray[4];
      d3r6 = sixArray[8];
      d3r7 = sixArray[31];
      d3r8 = sixArray[0];
    }
    if (digit3 == '3') {
      d3r1 = sixArray[14];
      d3r2 = sixArray[17];
      d3r3 = sixArray[1];
      d3r4 = sixArray[2];
      d3r5 = sixArray[1];
      d3r6 = sixArray[17];
      d3r7 = sixArray[14];
      d3r8 = sixArray[0];
    }
    if (digit3 == '4') {
      d3r1 = sixArray[2];
      d3r2 = sixArray[6];
      d3r3 = sixArray[10];
      d3r4 = sixArray[31];
      d3r5 = sixArray[2];
      d3r6 = sixArray[2];
      d3r7 = sixArray[2];
      d3r8 = sixArray[0];
    }
    if (digit3 == '5') {
      d3r1 = sixArray[31];
      d3r2 = sixArray[16];
      d3r3 = sixArray[16];
      d3r4 = sixArray[30];
      d3r5 = sixArray[1];
      d3r6 = sixArray[17];
      d3r7 = sixArray[14];
      d3r8 = sixArray[0];
    }
    if (digit3 == '6') {
      d3r1 = sixArray[6];
      d3r2 = sixArray[8];
      d3r3 = sixArray[16];
      d3r4 = sixArray[30];
      d3r5 = sixArray[17];
      d3r6 = sixArray[17];
      d3r7 = sixArray[14];
      d3r8 = sixArray[0];
    }
    if (digit3 == '7') {
      d3r1 = sixArray[31];
      d3r2 = sixArray[17];
      d3r3 = sixArray[2];
      d3r4 = sixArray[4];
      d3r5 = sixArray[4];
      d3r6 = sixArray[4];
      d3r7 = sixArray[4];
      d3r8 = sixArray[0];
    }
    if (digit3 == '8') {
      d3r1 = sixArray[14];
      d3r2 = sixArray[17];
      d3r3 = sixArray[17];
      d3r4 = sixArray[14];
      d3r5 = sixArray[17];
      d3r6 = sixArray[17];
      d3r7 = sixArray[14];
      d3r8 = sixArray[0];
    }
    if (digit3 == '9') {
      d3r1 = sixArray[14];
      d3r2 = sixArray[17];
      d3r3 = sixArray[17];
      d3r4 = sixArray[15];
      d3r5 = sixArray[1];
      d3r6 = sixArray[2];
      d3r7 = sixArray[12];
      d3r8 = sixArray[0];
    }
    if (digit3 == 'A') {
      d3r1 = sixArray[14];
      d3r2 = sixArray[17];
      d3r3 = sixArray[17];
      d3r4 = sixArray[17];
      d3r5 = sixArray[31];
      d3r6 = sixArray[17];
      d3r7 = sixArray[17];
      d3r8 = sixArray[0];
    }
    if (digit3 == 'B') {
      d3r1 = sixArray[30];
      d3r2 = sixArray[17];
      d3r3 = sixArray[17];
      d3r4 = sixArray[30];
      d3r5 = sixArray[17];
      d3r6 = sixArray[17];
      d3r7 = sixArray[30];
      d3r8 = sixArray[0];
    }
    if (digit3 == 'C') {
      d3r1 = sixArray[14];
      d3r2 = sixArray[17];
      d3r3 = sixArray[16];
      d3r4 = sixArray[16];
      d3r5 = sixArray[16];
      d3r6 = sixArray[17];
      d3r7 = sixArray[14];
      d3r8 = sixArray[0];
    }
    if (digit3 == 'D') {
      d3r1 = sixArray[28];
      d3r2 = sixArray[18];
      d3r3 = sixArray[17];
      d3r4 = sixArray[17];
      d3r5 = sixArray[17];
      d3r6 = sixArray[18];
      d3r7 = sixArray[28];
      d3r8 = sixArray[0];
    }
    if (digit3 == '-') {
      d3r1 = sixArray[0];
      d3r2 = sixArray[0];
      d3r3 = sixArray[0];
      d3r4 = sixArray[0];
      d3r5 = sixArray[0];
      d3r6 = sixArray[0];
      d3r7 = sixArray[0];
      d3r8 = sixArray[0];
    }

    //digit4
    if (digit4 == '0') {
      d4r1 = endArray[14];
      d4r2 = endArray[17];
      d4r3 = endArray[19];
      d4r4 = endArray[21];
      d4r5 = endArray[25];
      d4r6 = endArray[17];
      d4r7 = endArray[14];
      d4r8 = endArray[0];
    }
    if (digit4 == '1') {
      d4r1 = endArray[4];
      d4r2 = endArray[12];
      d4r3 = endArray[4];
      d4r4 = endArray[4];
      d4r5 = endArray[4];
      d4r6 = endArray[4];
      d4r7 = endArray[14];
      d4r8 = endArray[0];
    }
    if (digit4 == '2') {
      d4r1 = endArray[14];
      d4r2 = endArray[17];
      d4r3 = endArray[1];
      d4r4 = endArray[2];
      d4r5 = endArray[4];
      d4r6 = endArray[8];
      d4r7 = endArray[31];
      d4r8 = endArray[0];
    }
    if (digit4 == '3') {
      d4r1 = endArray[14];
      d4r2 = endArray[17];
      d4r3 = endArray[1];
      d4r4 = endArray[2];
      d4r5 = endArray[1];
      d4r6 = endArray[17];
      d4r7 = endArray[14];
      d4r8 = endArray[0];
    }
    if (digit4 == '4') {
      d4r1 = endArray[2];
      d4r2 = endArray[6];
      d4r3 = endArray[10];
      d4r4 = endArray[31];
      d4r5 = endArray[2];
      d4r6 = endArray[2];
      d4r7 = endArray[2];
      d4r8 = endArray[0];
    }
    if (digit4 == '5') {
      d4r1 = endArray[31];
      d4r2 = endArray[16];
      d4r3 = endArray[16];
      d4r4 = endArray[30];
      d4r5 = endArray[1];
      d4r6 = endArray[17];
      d4r7 = endArray[14];
      d4r8 = endArray[0];
    }
    if (digit4 == '6') {
      d4r1 = endArray[6];
      d4r2 = endArray[8];
      d4r3 = endArray[16];
      d4r4 = endArray[30];
      d4r5 = endArray[17];
      d4r6 = endArray[17];
      d4r7 = endArray[14];
      d4r8 = endArray[0];
    }
    if (digit4 == '7') {
      d4r1 = endArray[31];
      d4r2 = endArray[17];
      d4r3 = endArray[2];
      d4r4 = endArray[4];
      d4r5 = endArray[4];
      d4r6 = endArray[4];
      d4r7 = endArray[4];
      d4r8 = endArray[0];
    }
    if (digit4 == '8') {
      d4r1 = endArray[14];
      d4r2 = endArray[17];
      d4r3 = endArray[17];
      d4r4 = endArray[14];
      d4r5 = endArray[17];
      d4r6 = endArray[17];
      d4r7 = endArray[14];
      d4r8 = endArray[0];
    }
    if (digit4 == '9') {
      d4r1 = endArray[14];
      d4r2 = endArray[17];
      d4r3 = endArray[17];
      d4r4 = endArray[15];
      d4r5 = endArray[1];
      d4r6 = endArray[2];
      d4r7 = endArray[12];
      d4r8 = endArray[0];
    }
    if (digit4 == 'A') {
      d4r1 = endArray[14];
      d4r2 = endArray[17];
      d4r3 = endArray[17];
      d4r4 = endArray[17];
      d4r5 = endArray[31];
      d4r6 = endArray[17];
      d4r7 = endArray[17];
      d4r8 = endArray[0];
    }
    if (digit4 == 'B') {
      d4r1 = endArray[30];
      d4r2 = endArray[17];
      d4r3 = endArray[17];
      d4r4 = endArray[30];
      d4r5 = endArray[17];
      d4r6 = endArray[17];
      d4r7 = endArray[30];
      d4r8 = endArray[0];
    }
    if (digit4 == 'C') {
      d4r1 = endArray[14];
      d4r2 = endArray[17];
      d4r3 = endArray[16];
      d4r4 = endArray[16];
      d4r5 = endArray[16];
      d4r6 = endArray[17];
      d4r7 = endArray[14];
      d4r8 = endArray[0];
    }
    if (digit4 == 'D') {
      d4r1 = endArray[28];
      d4r2 = endArray[18];
      d4r3 = endArray[17];
      d4r4 = endArray[17];
      d4r5 = endArray[17];
      d4r6 = endArray[18];
      d4r7 = endArray[28];
      d4r8 = endArray[0];
    }
    if (digit4 == '-') {
      d4r1 = endArray[0];
      d4r2 = endArray[0];
      d4r3 = endArray[0];
      d4r4 = endArray[0];
      d4r5 = endArray[0];
      d4r6 = endArray[0];
      d4r7 = endArray[0];
      d4r8 = endArray[0];
    }

    /* ---------------------- */
    /* -- digit5 - Zeile 2 -- */
    /* ---------------------- */

    if (digit5 == '0') {
      d5r1 = sixArray[14];
      d5r2 = sixArray[17];
      d5r3 = sixArray[19];
      d5r4 = sixArray[21];
      d5r5 = sixArray[25];
      d5r6 = sixArray[17];
      d5r7 = sixArray[14];
    }
    if (digit5 == '1') {
      d5r1 = sixArray[4];
      d5r2 = sixArray[12];
      d5r3 = sixArray[4];
      d5r4 = sixArray[4];
      d5r5 = sixArray[4];
      d5r6 = sixArray[4];
      d5r7 = sixArray[14];
    }
    if (digit5 == '2') {
      d5r1 = sixArray[14];
      d5r2 = sixArray[17];
      d5r3 = sixArray[1];
      d5r4 = sixArray[2];
      d5r5 = sixArray[4];
      d5r6 = sixArray[8];
      d5r7 = sixArray[31];
    }
    if (digit5 == '3') {
      d5r1 = sixArray[14];
      d5r2 = sixArray[17];
      d5r3 = sixArray[1];
      d5r4 = sixArray[2];
      d5r5 = sixArray[1];
      d5r6 = sixArray[17];
      d5r7 = sixArray[14];
    }
    if (digit5 == '4') {
      d5r1 = sixArray[2];
      d5r2 = sixArray[6];
      d5r3 = sixArray[10];
      d5r4 = sixArray[31];
      d5r5 = sixArray[2];
      d5r6 = sixArray[2];
      d5r7 = sixArray[2];
    }
    if (digit5 == '5') {
      d5r1 = sixArray[31];
      d5r2 = sixArray[16];
      d5r3 = sixArray[16];
      d5r4 = sixArray[30];
      d5r5 = sixArray[1];
      d5r6 = sixArray[17];
      d5r7 = sixArray[14];
    }
    if (digit5 == '6') {
      d5r1 = sixArray[6];
      d5r2 = sixArray[8];
      d5r3 = sixArray[16];
      d5r4 = sixArray[30];
      d5r5 = sixArray[17];
      d5r6 = sixArray[17];
      d5r7 = sixArray[14];
    }
    if (digit5 == '7') {
      d5r1 = sixArray[31];
      d5r2 = sixArray[17];
      d5r3 = sixArray[2];
      d5r4 = sixArray[4];
      d5r5 = sixArray[4];
      d5r6 = sixArray[4];
      d5r7 = sixArray[4];
    }
    if (digit5 == '8') {
      d5r1 = sixArray[14];
      d5r2 = sixArray[17];
      d5r3 = sixArray[17];
      d5r4 = sixArray[14];
      d5r5 = sixArray[17];
      d5r6 = sixArray[17];
      d5r7 = sixArray[14];
    }
    if (digit5 == '9') {
      d5r1 = sixArray[14];
      d5r2 = sixArray[17];
      d5r3 = sixArray[17];
      d5r4 = sixArray[15];
      d5r5 = sixArray[1];
      d5r6 = sixArray[2];
      d5r7 = sixArray[12];
    }
    if (digit5 == 'A') {
      d5r1 = sixArray[14];
      d5r2 = sixArray[17];
      d5r3 = sixArray[17];
      d5r4 = sixArray[17];
      d5r5 = sixArray[31];
      d5r6 = sixArray[17];
      d5r7 = sixArray[17];
    }
    if (digit5 == 'B') {
      d5r1 = sixArray[30];
      d5r2 = sixArray[17];
      d5r3 = sixArray[17];
      d5r4 = sixArray[30];
      d5r5 = sixArray[17];
      d5r6 = sixArray[17];
      d5r7 = sixArray[30];
    }
    if (digit5 == 'C') {
      d5r1 = sixArray[14];
      d5r2 = sixArray[17];
      d5r3 = sixArray[16];
      d5r4 = sixArray[16];
      d5r5 = sixArray[16];
      d5r6 = sixArray[17];
      d5r7 = sixArray[14];
    }
    if (digit5 == 'D') {
      d5r1 = sixArray[28];
      d5r2 = sixArray[18];
      d5r3 = sixArray[17];
      d5r4 = sixArray[17];
      d5r5 = sixArray[17];
      d5r6 = sixArray[18];
      d5r7 = sixArray[28];
    }
    if (digit5 == '-') {
      d5r1 = sixArray[0];
      d5r2 = sixArray[0];
      d5r3 = sixArray[0];
      d5r4 = sixArray[0];
      d5r5 = sixArray[0];
      d5r6 = sixArray[0];
      d5r7 = sixArray[0];
    }

    //digit6
    if (digit6 == '0') {
      d6r1 = sixArray[14];
      d6r2 = sixArray[17];
      d6r3 = sixArray[19];
      d6r4 = sixArray[21];
      d6r5 = sixArray[25];
      d6r6 = sixArray[17];
      d6r7 = sixArray[14];
    }
    if (digit6 == '1') {
      d6r1 = sixArray[4];
      d6r2 = sixArray[12];
      d6r3 = sixArray[4];
      d6r4 = sixArray[4];
      d6r5 = sixArray[4];
      d6r6 = sixArray[4];
      d6r7 = sixArray[14];
    }
    if (digit6 == '2') {
      d6r1 = sixArray[14];
      d6r2 = sixArray[17];
      d6r3 = sixArray[1];
      d6r4 = sixArray[2];
      d6r5 = sixArray[4];
      d6r6 = sixArray[8];
      d6r7 = sixArray[31];
    }
    if (digit6 == '3') {
      d6r1 = sixArray[14];
      d6r2 = sixArray[17];
      d6r3 = sixArray[1];
      d6r4 = sixArray[2];
      d6r5 = sixArray[1];
      d6r6 = sixArray[17];
      d6r7 = sixArray[14];
    }
    if (digit6 == '4') {
      d6r1 = sixArray[2];
      d6r2 = sixArray[6];
      d6r3 = sixArray[10];
      d6r4 = sixArray[31];
      d6r5 = sixArray[2];
      d6r6 = sixArray[2];
      d6r7 = sixArray[2];
    }
    if (digit6 == '5') {
      d6r1 = sixArray[31];
      d6r2 = sixArray[16];
      d6r3 = sixArray[16];
      d6r4 = sixArray[30];
      d6r5 = sixArray[1];
      d6r6 = sixArray[17];
      d6r7 = sixArray[14];
    }
    if (digit6 == '6') {
      d6r1 = sixArray[6];
      d6r2 = sixArray[8];
      d6r3 = sixArray[16];
      d6r4 = sixArray[30];
      d6r5 = sixArray[17];
      d6r6 = sixArray[17];
      d6r7 = sixArray[14];
    }
    if (digit6 == '7') {
      d6r1 = sixArray[31];
      d6r2 = sixArray[17];
      d6r3 = sixArray[2];
      d6r4 = sixArray[4];
      d6r5 = sixArray[4];
      d6r6 = sixArray[4];
      d6r7 = sixArray[4];
    }
    if (digit6 == '8') {
      d6r1 = sixArray[14];
      d6r2 = sixArray[17];
      d6r3 = sixArray[17];
      d6r4 = sixArray[14];
      d6r5 = sixArray[17];
      d6r6 = sixArray[17];
      d6r7 = sixArray[14];
    }
    if (digit6 == '9') {
      d6r1 = sixArray[14];
      d6r2 = sixArray[17];
      d6r3 = sixArray[17];
      d6r4 = sixArray[15];
      d6r5 = sixArray[1];
      d6r6 = sixArray[2];
      d6r7 = sixArray[12];
    }
    if (digit6 == 'A') {
      d6r1 = sixArray[14];
      d6r2 = sixArray[17];
      d6r3 = sixArray[17];
      d6r4 = sixArray[17];
      d6r5 = sixArray[31];
      d6r6 = sixArray[17];
      d6r7 = sixArray[17];
    }
    if (digit6 == 'B') {
      d6r1 = sixArray[30];
      d6r2 = sixArray[17];
      d6r3 = sixArray[17];
      d6r4 = sixArray[30];
      d6r5 = sixArray[17];
      d6r6 = sixArray[17];
      d6r7 = sixArray[30];
    }
    if (digit6 == 'C') {
      d6r1 = sixArray[14];
      d6r2 = sixArray[17];
      d6r3 = sixArray[16];
      d6r4 = sixArray[16];
      d6r5 = sixArray[16];
      d6r6 = sixArray[17];
      d6r7 = sixArray[14];
    }
    if (digit6 == 'D') {
      d6r1 = sixArray[28];
      d6r2 = sixArray[18];
      d6r3 = sixArray[17];
      d6r4 = sixArray[17];
      d6r5 = sixArray[17];
      d6r6 = sixArray[18];
      d6r7 = sixArray[28];
    }
    if (digit6 == '-') {
      d6r1 = sixArray[0];
      d6r2 = sixArray[0];
      d6r3 = sixArray[0];
      d6r4 = sixArray[0];
      d6r5 = sixArray[0];
      d6r6 = sixArray[0];
      d6r7 = sixArray[0];
    }

    //digit7
    if (digit7 == '0') {
      d7r1 = sixArray[14];
      d7r2 = sixArray[17];
      d7r3 = sixArray[19];
      d7r4 = sixArray[21];
      d7r5 = sixArray[25];
      d7r6 = sixArray[17];
      d7r7 = sixArray[14];
    }
    if (digit7 == '1') {
      d7r1 = sixArray[4];
      d7r2 = sixArray[12];
      d7r3 = sixArray[4];
      d7r4 = sixArray[4];
      d7r5 = sixArray[4];
      d7r6 = sixArray[4];
      d7r7 = sixArray[14];
    }
    if (digit7 == '2') {
      d7r1 = sixArray[14];
      d7r2 = sixArray[17];
      d7r3 = sixArray[1];
      d7r4 = sixArray[2];
      d7r5 = sixArray[4];
      d7r6 = sixArray[8];
      d7r7 = sixArray[31];
    }
    if (digit7 == '3') {
      d7r1 = sixArray[14];
      d7r2 = sixArray[17];
      d7r3 = sixArray[1];
      d7r4 = sixArray[2];
      d7r5 = sixArray[1];
      d7r6 = sixArray[17];
      d7r7 = sixArray[14];
    }
    if (digit7 == '4') {
      d7r1 = sixArray[2];
      d7r2 = sixArray[6];
      d7r3 = sixArray[10];
      d7r4 = sixArray[31];
      d7r5 = sixArray[2];
      d7r6 = sixArray[2];
      d7r7 = sixArray[2];
    }
    if (digit7 == '5') {
      d7r1 = sixArray[31];
      d7r2 = sixArray[16];
      d7r3 = sixArray[16];
      d7r4 = sixArray[30];
      d7r5 = sixArray[1];
      d7r6 = sixArray[17];
      d7r7 = sixArray[14];
    }
    if (digit7 == '6') {
      d7r1 = sixArray[6];
      d7r2 = sixArray[8];
      d7r3 = sixArray[16];
      d7r4 = sixArray[30];
      d7r5 = sixArray[17];
      d7r6 = sixArray[17];
      d7r7 = sixArray[14];
    }
    if (digit7 == '7') {
      d7r1 = sixArray[31];
      d7r2 = sixArray[17];
      d7r3 = sixArray[2];
      d7r4 = sixArray[4];
      d7r5 = sixArray[4];
      d7r6 = sixArray[4];
      d7r7 = sixArray[4];
    }
    if (digit7 == '8') {
      d7r1 = sixArray[14];
      d7r2 = sixArray[17];
      d7r3 = sixArray[17];
      d7r4 = sixArray[14];
      d7r5 = sixArray[17];
      d7r6 = sixArray[17];
      d7r7 = sixArray[14];
    }
    if (digit7 == '9') {
      d7r1 = sixArray[14];
      d7r2 = sixArray[17];
      d7r3 = sixArray[17];
      d7r4 = sixArray[15];
      d7r5 = sixArray[1];
      d7r6 = sixArray[2];
      d7r7 = sixArray[12];
    }
    if (digit7 == 'A') {
      d7r1 = sixArray[14];
      d7r2 = sixArray[17];
      d7r3 = sixArray[17];
      d7r4 = sixArray[17];
      d7r5 = sixArray[31];
      d7r6 = sixArray[17];
      d7r7 = sixArray[17];
    }
    if (digit7 == 'B') {
      d7r1 = sixArray[30];
      d7r2 = sixArray[17];
      d7r3 = sixArray[17];
      d7r4 = sixArray[30];
      d7r5 = sixArray[17];
      d7r6 = sixArray[17];
      d7r7 = sixArray[30];
    }
    if (digit7 == 'C') {
      d7r1 = sixArray[14];
      d7r2 = sixArray[17];
      d7r3 = sixArray[16];
      d7r4 = sixArray[16];
      d7r5 = sixArray[16];
      d7r6 = sixArray[17];
      d7r7 = sixArray[14];
    }
    if (digit7 == 'D') {
      d7r1 = sixArray[28];
      d7r2 = sixArray[18];
      d7r3 = sixArray[17];
      d7r4 = sixArray[17];
      d7r5 = sixArray[17];
      d7r6 = sixArray[18];
      d7r7 = sixArray[28];
    }
    if (digit7 == '-') {
      d7r1 = sixArray[0];
      d7r2 = sixArray[0];
      d7r3 = sixArray[0];
      d7r4 = sixArray[0];
      d7r5 = sixArray[0];
      d7r6 = sixArray[0];
      d7r7 = sixArray[0];
    }

    //digit8
    if (digit8 == '0') {
      d8r1 = endArray[14];
      d8r2 = endArray[17];
      d8r3 = endArray[19];
      d8r4 = endArray[21];
      d8r5 = endArray[25];
      d8r6 = endArray[17];
      d8r7 = endArray[14];
    }
    if (digit8 == '1') {
      d8r1 = endArray[4];
      d8r2 = endArray[12];
      d8r3 = endArray[4];
      d8r4 = endArray[4];
      d8r5 = endArray[4];
      d8r6 = endArray[4];
      d8r7 = endArray[14];
    }
    if (digit8 == '2') {
      d8r1 = endArray[14];
      d8r2 = endArray[17];
      d8r3 = endArray[1];
      d8r4 = endArray[2];
      d8r5 = endArray[4];
      d8r6 = endArray[8];
      d8r7 = endArray[31];
    }
    if (digit8 == '3') {
      d8r1 = endArray[14];
      d8r2 = endArray[17];
      d8r3 = endArray[1];
      d8r4 = endArray[2];
      d8r5 = endArray[1];
      d8r6 = endArray[17];
      d8r7 = endArray[14];
    }
    if (digit8 == '4') {
      d8r1 = endArray[2];
      d8r2 = endArray[6];
      d8r3 = endArray[10];
      d8r4 = endArray[31];
      d8r5 = endArray[2];
      d8r6 = endArray[2];
      d8r7 = endArray[2];
    }
    if (digit8 == '5') {
      d8r1 = endArray[31];
      d8r2 = endArray[16];
      d8r3 = endArray[16];
      d8r4 = endArray[30];
      d8r5 = endArray[1];
      d8r6 = endArray[17];
      d8r7 = endArray[14];
    }
    if (digit8 == '6') {
      d8r1 = endArray[6];
      d8r2 = endArray[8];
      d8r3 = endArray[16];
      d8r4 = endArray[30];
      d8r5 = endArray[17];
      d8r6 = endArray[17];
      d8r7 = endArray[14];
    }
    if (digit8 == '7') {
      d8r1 = endArray[31];
      d8r2 = endArray[17];
      d8r3 = endArray[2];
      d8r4 = endArray[4];
      d8r5 = endArray[4];
      d8r6 = endArray[4];
      d8r7 = endArray[4];
    }
    if (digit8 == '8') {
      d8r1 = endArray[14];
      d8r2 = endArray[17];
      d8r3 = endArray[17];
      d8r4 = endArray[14];
      d8r5 = endArray[17];
      d8r6 = endArray[17];
      d8r7 = endArray[14];
    }
    if (digit8 == '9') {
      d8r1 = endArray[14];
      d8r2 = endArray[17];
      d8r3 = endArray[17];
      d8r4 = endArray[15];
      d8r5 = endArray[1];
      d8r6 = endArray[2];
      d8r7 = endArray[12];
    }
    if (digit8 == 'A') {
      d8r1 = endArray[14];
      d8r2 = endArray[17];
      d8r3 = endArray[17];
      d8r4 = endArray[17];
      d8r5 = endArray[31];
      d8r6 = endArray[17];
      d8r7 = endArray[17];
    }
    if (digit8 == 'B') {
      d8r1 = endArray[30];
      d8r2 = endArray[17];
      d8r3 = endArray[17];
      d8r4 = endArray[30];
      d8r5 = endArray[17];
      d8r6 = endArray[17];
      d8r7 = endArray[30];
    }
    if (digit8 == 'C') {
      d8r1 = endArray[14];
      d8r2 = endArray[17];
      d8r3 = endArray[16];
      d8r4 = endArray[16];
      d8r5 = endArray[16];
      d8r6 = endArray[17];
      d8r7 = endArray[14];
    }
    if (digit8 == 'D') {
      d8r1 = endArray[28];
      d8r2 = endArray[18];
      d8r3 = endArray[17];
      d8r4 = endArray[17];
      d8r5 = endArray[17];
      d8r6 = endArray[18];
      d8r7 = endArray[28];
    }
    if (digit8 == '-') {
      d8r1 = endArray[0];
      d8r2 = endArray[0];
      d8r3 = endArray[0];
      d8r4 = endArray[0];
      d8r5 = endArray[0];
      d8r6 = endArray[0];
      d8r7 = endArray[0];
    }

    /* ---------------------------- */
    /* ---- Zusammensetzen der ---- */
    /* --- der einzelnen Zeilen --- */
    /* ---- zum Erzeugen einer ---- */
    /* ---  Binärzahl pro Zeile --- */
    /* ---------------------------- */

    //Zeile 1
    long r11 = holder | d1r1;
    long r12 = r11 << 6;
    long r13 = r12 | d2r1;
    long r14 = r13 << 6;
    long r15 = r14 | d3r1;
    long r16 = r15 << 6;
    long r17 = r16 | d4r1;
    r1 = r17 >> 1;

    //Zeile 2
    long r21 = holder | d1r2;
    long r22 = r21 << 6;
    long r23 = r22 | d2r2;
    long r24 = r23 << 6;
    long r25 = r24 | d3r2;
    long r26 = r25 << 6;
    long r27 = r26 | d4r2;
    r2 = r27 >> 1;

    //Zeile 3
    long r31 = holder | d1r3;
    long r32 = r31 << 6;
    long r33 = r32 | d2r3;
    long r34 = r33 << 6;
    long r35 = r34 | d3r3;
    long r36 = r35 << 6;
    long r37 = r36 | d4r3;
    r3 = r37 >> 1;

    //Zeile 4
    long r41 = holder | d1r4;
    long r42 = r41 << 6;
    long r43 = r42 | d2r4;
    long r44 = r43 << 6;
    long r45 = r44 | d3r4;
    long r46 = r45 << 6;
    long r47 = r46 | d4r4;
    r4 = r47 >> 1;

    //Zeile 5
    long r51 = holder | d1r5;
    long r52 = r51 << 6;
    long r53 = r52 | d2r5;
    long r54 = r53 << 6;
    long r55 = r54 | d3r5;
    long r56 = r55 << 6;
    long r57 = r56 | d4r5;
    r5 = r57 >> 1;

    //Zeile 6
    long r61 = holder | d1r6;
    long r62 = r61 << 6;
    long r63 = r62 | d2r6;
    long r64 = r63 << 6;
    long r65 = r64 | d3r6;
    long r66 = r65 << 6;
    long r67 = r66 | d4r6;
    r6 = r67 >> 1;

    //Zeile 7
    long r71 = holder | d1r7;
    long r72 = r71 << 6;
    long r73 = r72 | d2r7;
    long r74 = r73 << 6;
    long r75 = r74 | d3r7;
    long r76 = r75 << 6;
    long r77 = r76 | d4r7;
    r7 = r77 >> 1;

    //Zeile 8
    long r81 = holder | d1r8;
    long r82 = r81 << 6;
    long r83 = r82 | d2r8;
    long r84 = r83 << 6;
    long r85 = r84 | d3r8;
    long r86 = r85 << 6;
    long r87 = r86 | d4r8;
    r8 = r87 >> 1;

    //Zeile 9
    long r91 = holder | d5r1;
    long r92 = r91 << 6;
    long r93 = r92 | d6r1;
    long r94 = r93 << 6;
    long r95 = r94 | d7r1;
    long r96 = r95 << 6;
    long r97 = r96 | d8r1;
    r9 = r97 >> 1;

    //Zeile 10
    long r101 = holder | d5r2;
    long r102 = r101 << 6;
    long r103 = r102 | d6r2;
    long r104 = r103 << 6;
    long r105 = r104 | d7r2;
    long r106 = r105 << 6;
    long r107 = r106 | d8r2;
    rr10 = r107 >> 1; //doppel r wegen Überschneidung mit Zeile 1

    //Zeile 11
    long r111 = holder | d5r3;
    long r112 = r111 << 6;
    long r113 = r112 | d6r3;
    long r114 = r113 << 6;
    long r115 = r114 | d7r3;
    long r116 = r115 << 6;
    long r117 = r116 | d8r3;
    rr11 = r117 >> 1;

    //Zeile 12
    long r121 = holder | d5r4;
    long r122 = r121 << 6;
    long r123 = r122 | d6r4;
    long r124 = r123 << 6;
    long r125 = r124 | d7r4;
    long r126 = r125 << 6;
    long r127 = r126 | d8r4;
    rr12 = r127 >> 1;

    //Zeile 13
    long r131 = holder | d5r5;
    long r132 = r131 << 6;
    long r133 = r132 | d6r5;
    long r134 = r133 << 6;
    long r135 = r134 | d7r5;
    long r136 = r135 << 6;
    long r137 = r136 | d8r5;
    rr13 = r137 >> 1;

    //Zeile 14
    long r141 = holder | d5r6;
    long r142 = r141 << 6;
    long r143 = r142 | d6r6;
    long r144 = r143 << 6;
    long r145 = r144 | d7r6;
    long r146 = r145 << 6;
    long r147 = r146 | d8r6;
    rr14 = r147 >> 1;

    //Zeile 15
    long r151 = holder | d5r7;
    long r152 = r151 << 6;
    long r153 = r152 | d6r7;
    long r154 = r153 << 6;
    long r155 = r154 | d7r7;
    long r156 = r155 << 6;
    long r157 = r156 | d8r7;
    rr15 = r157 >> 1;

    //Kontrolle der einzelnen Zeileneinträge in BIN
    Serial.println("...");
    Serial.print("Zeile  1: ");
    Serial.println(r1, BIN);
    Serial.print("Zeile  2: ");
    Serial.println(r2, BIN);
    Serial.print("Zeile  3: ");
    Serial.println(r3, BIN);
    Serial.print("Zeile  4: ");
    Serial.println(r4, BIN);
    Serial.print("Zeile  5: ");
    Serial.println(r5, BIN);
    Serial.print("Zeile  6: ");
    Serial.println(r6, BIN);
    Serial.print("Zeile  7: ");
    Serial.println(r7, BIN);
    Serial.print("Zeile  8: ");
    Serial.println(r8, BIN);
    Serial.print("Zeile  9: ");
    Serial.println(r9, BIN);
    Serial.print("Zeile 10: ");
    Serial.println(rr10, BIN);
    Serial.print("Zeile 11: ");
    Serial.println(rr11, BIN);
    Serial.print("Zeile 12: ");
    Serial.println(rr12, BIN);
    Serial.print("Zeile 13: ");
    Serial.println(rr13, BIN);
    Serial.print("Zeile 14: ");
    Serial.println(rr14, BIN);
    Serial.print("Zeile 15: ");
    Serial.println(rr15, BIN);
  }
  else {
    // Ausgabe auf die Schieberegister
    // Wenn keine neuen Daten empfangen werden

    //Zeile 1
    col1 = r1 >> 16;
    colH = r1 >> 8;
    col2 = colH & mask;
    col3 = r1 & mask;

    rowA = row1 >> 16;
    rowB = row1 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 1:  ");
    Serial.println(r1, BIN);

    //Zeile 2
    col1 = r2 >> 16;
    colH = r2 >> 8;
    col2 = colH & mask;
    col3 = r2 & mask;

    rowA = row2 >> 16;
    rowB = row2 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 2:  ");
    Serial.println(r2, BIN);

    //Zeile 3
    col1 = r3 >> 16;
    colH = r3 >> 8;
    col2 = colH & mask;
    col3 = r3 & mask;

    rowA = row3 >> 16;
    rowB = row3 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 3:  ");
    Serial.println(r3, BIN);

    //Zeile 4
    col1 = r4 >> 16;
    colH = r4 >> 8;
    col2 = colH & mask;
    col3 = r4 & mask;

    rowA = row4 >> 16;
    rowB = row4 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 4:  ");
    Serial.println(r4, BIN);

    //Zeile 5
    col1 = r5 >> 16;
    colH = r5 >> 8;
    col2 = colH & mask;
    col3 = r5 & mask;

    rowA = row5 >> 16;
    rowB = row5 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 5:  ");
    Serial.println(r5, BIN);

    //Zeile 6
    col1 = r6 >> 16;
    colH = r6 >> 8;
    col2 = colH & mask;
    col3 = r6 & mask;

    rowA = row6 >> 16;
    rowB = row6 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 6:  ");
    Serial.println(r6, BIN);

    //Zeile 7
    col1 = r7 >> 16;
    colH = r7 >> 8;
    col2 = colH & mask;
    col3 = r7 & mask;

    rowA = row7 >> 16;
    rowB = row7 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 7:  ");
    Serial.println(r7, BIN);

    //Zeile 8
    col1 = r8 >> 16;
    colH = r8 >> 8;
    col2 = colH & mask;
    col3 = r8 & mask;

    rowA = row8 >> 16;
    rowB = row8 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 8:  ");
    Serial.println(r8, BIN);

    //Zeile 9
    col1 = r9 >> 16;
    colH = r9 >> 8;
    col2 = colH & mask;
    col3 = r9 & mask;

    rowA = row9 >> 16;
    rowB = row9 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 9:  ");
    Serial.println(r9, BIN);

    //Zeile 10
    col1 = rr10 >> 16;
    colH = rr10 >> 8;
    col2 = colH & mask;
    col3 = rr10 & mask;

    rowA = row10 >> 16;
    rowB = row10 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 10: ");
    Serial.println(rr10, BIN);

    //Zeile 11
    col1 = rr11 >> 16;
    colH = rr11 >> 8;
    col2 = colH & mask;
    col3 = rr11 & mask;

    rowA = row11 >> 16;
    rowB = row11 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 11: ");
    Serial.println(rr11, BIN);

    //Zeile 12
    col1 = rr12 >> 16;
    colH = rr12 >> 8;
    col2 = colH & mask;
    col3 = rr12 & mask;

    rowA = row12 >> 16;
    rowB = row12 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 12: ");
    Serial.println(rr12, BIN);

    //Zeile 13
    col1 = rr13 >> 16;
    colH = rr13 >> 8;
    col2 = colH & mask;
    col3 = rr13 & mask;

    rowA = row13 >> 16;
    rowB = row13 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 13: ");
    Serial.println(rr13, BIN);

    //Zeile 14
    col1 = rr14 >> 16;
    colH = rr14 >> 8;
    col2 = colH & mask;
    col3 = rr14 & mask;

    rowA = row14 >> 16;
    rowB = row14 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 14: ");
    Serial.println(rr14, BIN);

    //Zeile 15
    col1 = rr15 >> 16;
    colH = rr15 >> 8;
    col2 = colH & mask;
    col3 = rr15 & mask;

    rowA = row15 >> 16;
    rowB = row15 >> 8;

    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowA);
    shiftOut(dataPin2, clockPin2, LSBFIRST, rowB);
    digitalWrite(latchPin2, HIGH);
    delay(1);
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col1);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col2);
    shiftOut(dataPin3, clockPin3, LSBFIRST, col3);
    digitalWrite(latchPin3, HIGH);
    delay(1);

    Serial.print("Zeile 15: ");
    Serial.println(rr15, BIN);
  }
}

//Copyright by Tom Schröter und Oliver Reichardt
