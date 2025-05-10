int buzzer = 3;

#define BUTTON1 A1 
#define BUTTON2 A2 

void setup() { 

 pinMode(buzzer, OUTPUT);

} 

void loop() { 

 unsigned char i, j;
if(!digitalRead(BUTTON1)) 

{ 
digitalWrite(buzzer, HIGH);
delay(1);
} 

if(!digitalRead(BUTTON2)) 
{ 
digitalWrite(buzzer, LOW);

delay(1);
} 

 } 



 