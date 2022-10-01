//----------------------------------------------------
// Fungsi LCD satu baris String
void lcdPrint(byte x, byte y, String msg) {
  lcd.setCursor(x, y);
  lcd.print(msg);
}
//----------------------------------------------------
// Fungsi LCD satu baris Char Array
void lcdPrint(byte x, byte y, char* msg) {
  lcd.setCursor(x, y);
  lcd.print(msg);
}
//----------------------------------------------------
String parseData() {
  String raw, data[5];
  bool parsing = false;
  int x = 0;
  if (Serial.available() > 0) {
    raw = Serial.readStringUntil('\n');
    parsing = true;
  }
  if (parsing) {
    for (int i = 0; i < raw.length(); i++) {
      if (raw[i] == '+' or raw[i] == ' ') {
        x++; data[x] = "";
      } else {
        data[x] += raw[i];
      }
    }
    Serial.print(F("BERAT: "));
    Serial.print(data[1]);
    Serial.println(F(" gram"));

    return String(data[1]);
  }
  return "";
}
//----------------------------------------------------
float fixFloat(float f) {
  float d1 = (long)f;
  float d2 = (long(f * 1000) % 1000);
  d2 = d2 / 1000;
  float ff = d1 + d2;
  return ff;
}
//----------------------------------------------------
void resetData() {
  timbangan = 1;
  hasil = 0;
  lcd.clear();
}
//----------------------------------------------------
void beep(int wait) {
  digitalWrite(BUZZER, ON);
  delay(wait);
  digitalWrite(BUZZER, OFF);
}
//----------------------------------------------------
