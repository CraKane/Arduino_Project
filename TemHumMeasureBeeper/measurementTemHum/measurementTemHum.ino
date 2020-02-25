#include <LiquidCrystal.h>
#include<DHT.h>
#define RS 12
#define Enable 11
#define d4 5
#define d5 4
#define d6 3
#define d7 2
#define Beep 6
#define DHTPIN 7
#define DHTTYPE DHT11

DHT Dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(RS, Enable, d4, d5, d6, d7);
bool flag = false;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Dht.begin();
  Serial.begin(9600);
  lcd.print("hello, world!");
  delay(2000);
}
void loop() {
  // put your main code here, to run repeatedly:
  float t = Dht.readTemperature();
  float h = Dht.readHumidity();
  lcd.clear();
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("H: ");
  lcd.print(h);
  lcd.setCursor(0, 1);
  lcd.print("T: ");
  lcd.print(t);
  lcd.print(" degrees");
  delay(1000);
  if(!flag){
    if(t >= 33 && h > 90){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Too hot! Too wet!");
      flag = true;
      tone(Beep, 2500);
      delay(3000);
      noTone(Beep);
    }
    else if(t >= 33){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Too hot!");
      flag = true; 
      tone(Beep, 900);
      delay(2500);
      noTone(Beep); 
    }
    else if(h > 90){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Too wet!");
      flag = true;
      tone(Beep, 900);
      delay(2500);
      noTone(Beep);  
    }
  }  
  delay(480);
}
