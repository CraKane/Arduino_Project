int pin = 5;

void setup()
{
   Serial.begin(9600);
   pinMode(pin, OUTPUT);
}
void loop()
{
   tone(pin, 512);
   delay(500);
   noTone(pin);
   tone(pin, 512);
   delay(500);
   noTone(pin);
  tone(pin, 768);
   delay(500);
   noTone(pin);
   tone(pin, 768);
   delay(500);
   noTone(pin);
   tone(pin, 853);
   delay(500);
   noTone(pin);
   tone(pin, 853);
   delay(500);
   noTone(pin);
   tone(pin, 768);
   delay(1000);
   noTone(pin);
   tone(pin, 682.666);
   delay(500);
   noTone(pin);
   tone(pin, 682.666);
   delay(500);
   noTone(pin);
   tone(pin, 640);
   delay(500);
   noTone(pin);
   tone(pin, 640);
   delay(500);
   noTone(pin);
   tone(pin, 576);
   delay(500);
   noTone(pin);
   tone(pin, 576);
   delay(500);
   noTone(pin);
   tone(pin, 512);
   delay(500);
   noTone(pin);
   delay(10000);
}

