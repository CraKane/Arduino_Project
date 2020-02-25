#define beep 7
#define fireSensor A5
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(beep, OUTPUT);
  pinMode(fireSensor, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(fireSensor);
  Serial.println(value);
  int i, j;
  if(value >= 600){
    for(j = 0; j < 2; j++){
        for(i = 0;i<15;i++)//输出一个频率的声音
        {
          tone(beep, 800);// frequency is 800 hz per second
          delay(100);//延时1ms
          tone(beep, 1000);
          delay(100);//延时ms
        }
        for(i=0;i<15;i++)//输出另一个频率的声音,这里的100与前面的80一样，用来控制频率，可以自己调节
        {
          tone(beep, 600);
          delay(100);
          tone(beep, 1500);
          delay(100);
        }
      }
    }
  else
    noTone(beep);
}
