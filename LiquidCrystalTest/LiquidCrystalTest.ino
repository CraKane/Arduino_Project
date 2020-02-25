#include <LiquidCrystal.h>
#define RS 12
#define Enable 11
#define d4 5
#define d5 4
#define d6 3
#define d7 2
LiquidCrystal lcd(RS, Enable, d4, d5, d6, d7);
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
}
void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  lcd.print("hello, world!");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("hello, world!");
  delay(1000);
  lcd.clear();
  delay(1000);
}
