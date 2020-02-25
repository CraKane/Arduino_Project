const int s_pin = A5;
const int beep = 6;
int val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(s_pin, INPUT);
  pinMode(beep, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(s_pin);
  Serial.println(val);

  if(val > 150){
    int t = 0;
    while(t < 3){
      t++;
      tone(beep, 1000);
      delay(500);
      tone(beep, 800);
      delay(500);
      tone(beep, 1200); 
      delay(500); 
    }
    noTone(beep);
  }
  else{
    noTone(beep);
  }
}
