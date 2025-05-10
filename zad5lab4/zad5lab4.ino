int led1 = 13; 

int led2 = 12; 

int led3 = 11; 

int led4 = 10; 

 

#define BUTTON1 A1 

#define BUTTON2 A2 

 



void setup() 

{ 

pinMode(led1, OUTPUT); 

pinMode(led2, OUTPUT); 

pinMode(led3, OUTPUT); 

pinMode(led4, OUTPUT); 

} 


void loop() 

{ 

if(!digitalRead(BUTTON1)) 

{ 

digitalWrite(led1, HIGH); 

digitalWrite(led2, HIGH); 

digitalWrite(led3, HIGH); 

digitalWrite(led4, HIGH); 

} 

if(!digitalRead(BUTTON2)) 

{ 

digitalWrite(led1, LOW); 

digitalWrite(led2, LOW); 

digitalWrite(led3, LOW); 

digitalWrite(led4, LOW); 

} 

} 