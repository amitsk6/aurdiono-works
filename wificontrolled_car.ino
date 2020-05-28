
#include <ESP8266WiFi.h>

#define TRIGGER 4
#define ECHO    5

WiFiClient client;
WiFiServer server(80);

const char* ssid = "defective_spider";
const char* password = "12345678";

String  data =""; 

/* define L298N or L293D motor control pins */
int leftMotorForward = 2;     /* GPIO2(D4) -> IN3   */
int rightMotorForward = 15;   /* GPIO15(D8) -> IN1  */
int leftMotorBackward = 0;    /* GPIO0(D3) -> IN4   */
int rightMotorBackward = 13;  /* GPIO13(D7) -> IN2  */


/* define L298N or L293D enable pins */
int rightMotorENB = 14; /* GPIO14(D5) -> Motor-A Enable */
int leftMotorENB = 12;  /* GPIO12(D6) -> Motor-B Enable */

void setup()
{Serial.begin (9600);
 
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(leftMotorBackward, OUTPUT);  
  pinMode(rightMotorBackward, OUTPUT);

  /* initialize motor enable pins as output */
  pinMode(leftMotorENB, OUTPUT); 
  pinMode(rightMotorENB, OUTPUT);

  /* start server communication */
  server.begin();
}

void loop()
{ 
    client = server.available();
    if (!client) return; 
    data = checkClient ();
    
    long duration, d;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  d = (duration/2) / 29.1;
  Serial.println(d);
if(d>5)
{
  Serial.println("Edge detected\n");
  MotorStop;
  if(data == "backward") MotorBackward();
}
else{
    if (data == "forward") MotorForward();
  
    else if (data == "backward") MotorBackward();
   
    else if (data == "left") TurnLeft();
    else if (data == "right") TurnRight();
    
    else if (data == "stop") MotorStop();
} }


void MotorForward(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

void MotorBackward(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorBackward,HIGH);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
}

/********************************************* TURN LEFT *****************************************************/
void TurnLeft(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH); 
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,HIGH);  
}

void TurnRight(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
}


void MotorStop(void)   
{
  digitalWrite(leftMotorENB,LOW);
  digitalWrite(rightMotorENB,LOW);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}


String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
