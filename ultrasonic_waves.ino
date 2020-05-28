int echo =13;
int trig =10;
void setup() {
  // put your setup code here, to run once:
pinMode(echo,INPUT);
pinMode(trig,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 float distance, duration;
digitalWrite(trig,LOW);
delayMicroseconds(10);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(echo,HIGH);
duration = pulseIn(echo,HIGH);
distance = (duration/2)*0.0270;
delay(200);
Serial.println(distance);
}
