#include "SPI.h"
#include "Phpoc.h"
#include <Servo.h>

PhpocServer server(80);
Servo servo_x;
Servo servo_y;

void setup() {
	Serial.begin(9600);
	while(!Serial)
		;

	Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);
	//Phpoc.begin();

	server.beginWebSocket("web_joystick");

	Serial.print("WebSocket server address : ");
	Serial.println(Phpoc.localIP());
	
	servo_x.attach(8);  // attaches the servo on pin 8 to the servo object
	servo_y.attach(9);  // attaches the servo on pin 9 to the servo object
	
	servo_x.write(90); 
	servo_y.write(90); 
	
}

void loop() {
	// wait for a new client:
	PhpocClient client = server.available();

	if (client) {
		String data = client.readLine();

		if(data){
			int pos = data.indexOf(':');
			long x = data.substring(0, pos).toInt();
			long y = data.substring(pos+1).toInt();
			
			Serial.print("x:");
			Serial.print(x);
			Serial.print(", y:");
			Serial.println(y);
			
			// scale  from [-100; 100] to [0; 180]
			long angle_x = (x + 100) * 180 /200;
			long angle_y = (y + 100) * 180 /200;
			
			servo_x.write(angle_x); 
			servo_y.write(angle_y); 
		}
	}
}