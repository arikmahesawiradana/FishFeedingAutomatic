#include <ESP32Time.h>
#include <LiquidCrystal_I2C.h>
#define servo 19
#define suhu 14

int lcdColumns = 16;
int lcdRows = 2;

ESP32Time rtc(3600);  // offset in seconds GMT+1
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup() {
  Serial.begin(115200);
  rtc.setTime(30, 45, 14, 20, 12, 2022);  // 17th Jan 2021 15:24:30
  pinMode(servo, OUTPUT);
  pinMode(suhu, INPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  struct tm timeinfo = rtc.getTimeStruct();
  lcd.setCursor(0, 0);
  lcd.print(&timeinfo, "Waktu: %H:%M:%S");   //  (tm struct) Sunday, January 17 2021 07:24:38
  int temp = analogRead(suhu);
  lcd.setCursor(0,1);
  lcd.print("suhu: ");
  lcd.print(temp);
  if(timeinfo.tm_hour >= 7 && timeinfo.tm_min <= 0){
    analogWrite(servo, 255);
  }
  else if(timeinfo.tm_hour >= 5 && timeinfo.tm_min <= 0){
    analogWrite(servo, 255);
  }
  else {
    analogWrite(servo, 0);
  }
}
