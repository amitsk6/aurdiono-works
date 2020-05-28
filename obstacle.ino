const int trig = 12;
const int echo = 11;
const int fwdleft5 = 8;
const int revleft4= 3;
const int fwdright7 = 4;
const int revright6 = 5;

 
int duration = 0;
int distance = 0;
#include <Servo.h>

Servo myservo;  

int pos = 0;  

 
void setup() 
{
  pinMode(trig , OUTPUT);
  pinMode(echo , INPUT);
  pinMode(fwdleft5, OUTPUT);
  pinMode(revleft4, OUTPUT);
  pinMode(fwdright7 , OUTPUT);
  pinMode(revright6, OUTPUT);
  
  Serial.begin(9600);
 
}
 
void loop()
{

 
  digitalWrite(trig , HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig , LOW);
 
 
  duration = pulseIn(echo , HIGH);
  distance = (duration/2) / 28.5 ;
  Serial.println(distance);
  
 
  if ( distance < 20 )
  {
    digitalWrite(fwdleft5, LOW);
    digitalWrite(revleft4,LOW);
    digitalWrite(fwdright7, HIGH);
    digitalWrite(revright6, LOW);
    delay(100);
  } 
  else
  {
             digitalWrite(fwdright7, HIGH);          
             digitalWrite(revright6, LOW);
             digitalWrite(fwdleft5, HIGH);                                
             digitalWrite(revleft4, LOW);
             delay(100);
            
            }
 delay(100);
}
