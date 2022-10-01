//----------------------------------------------------
// PIN LCD: SDA = A4, SCL = A5
// PIN BUZZER: A1 +   GND -
// PIN BUTTON: A0 dan GND
// PIN SERIAL TIMBANGAN: 0 dan 1

//----------------------------------------------------
// Library File
#include <LiquidCrystal_I2C.h>

#define BUTTON    A0
#define BUZZER    A1

#define BOUNCE    50
#define ON        HIGH
#define OFF       LOW

//-----------------------------
// Global Variable
char lcdBuff[20];
int timbangan;
String baca;
double baca1;
double baca2;
double hasil;
bool cek;
LiquidCrystal_I2C lcd(0x27, 16, 2);
//----------------------------------------------------
// Setup
void setup() {
  Serial.begin(9600);
  lcd.begin();

  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  lcdPrint(0, 0, "   -VGA  HUB-   ");
  lcdPrint(0, 1, "   ALDI FITRA   ");
  delay(3000);
  lcd.clear();

  timbangan = 1;
}
//----------------------------------------------------
// Looping
void loop() {
  if (timbangan == 1) {
    lcdPrint(0, 0, " TIMBANG KERING ");
    baca = parseData();
    if (baca != "") {
      beep(500);
      baca1 = fixFloat(baca.toDouble());
      Serial.println(baca1, 5);
      timbangan = 2;
      sprintf(lcdBuff, "   %5d.%03d g   ", (int)baca1, (long(baca1 * 1000) % 1000));
      lcdPrint(0, 1, baca);
      delay(3000);
      lcd.clear();
      Serial.println(baca1, 5);
    }
    if (digitalRead(BUTTON) == LOW) {
      while (digitalRead(BUTTON) == LOW) {}
      delay(BOUNCE);
      resetData();
    }
  } else if (timbangan == 2) {
    lcdPrint(0, 0, " TIMBANG  BASAH ");
    baca = parseData();
    if (baca != "") {
      beep(500);
      baca2 = fixFloat(baca.toDouble());
      Serial.println(baca2, 5);
      timbangan = 3;
       sprintf(lcdBuff, "   %5d.%03d g   ", (int)baca2, (long(baca2 * 1000) % 1000));
      lcdPrint(0, 1, baca);
      delay(3000);
      lcd.clear();
      cek = true;
      hasil = (float)baca1 / (float)baca2;
      hasil = fixFloat(hasil);
      if (cek) {
        Serial.println(baca1, 5);
        Serial.println(baca2, 5);
        Serial.println(hasil, 5);
        cek = false;
      }
    }
    if (digitalRead(BUTTON) == LOW) {
      while (digitalRead(BUTTON) == LOW) {}
      delay(BOUNCE);
      cek = false;
      resetData();
    }
  } else {
    lcdPrint(0, 0, "      HASIL     ");
    sprintf(lcdBuff, "   %5d.%03d     ", (int)hasil, (long(hasil * 1000) % 1000));
    lcdPrint(0, 1, lcdBuff);
    if (digitalRead(BUTTON) == LOW) {
      while (digitalRead(BUTTON) == LOW) {}
      delay(BOUNCE);
      resetData();
      cek = false;
    }
  }
}
//----------------------------------------------------
