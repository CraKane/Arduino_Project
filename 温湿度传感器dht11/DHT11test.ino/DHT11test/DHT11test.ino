#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11

DHT Dht(DHTPIN, DHTTYPE);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  float h = Dht.readHumidity();
  float t = Dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.println(h);
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("℃");
}
