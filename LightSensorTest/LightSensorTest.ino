const int led = 13;
const int cds = A5;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val;
  val = analogRead(cds);
  if(val > 512)///512 = 2.5v,可以自己调试，
  //传感器越敏感数值调高，越迟顿数值调低
  {
    digitalWrite(led, HIGH);  
  }
  else
  {
    digitalWrite(led, LOW);  
  }
}
