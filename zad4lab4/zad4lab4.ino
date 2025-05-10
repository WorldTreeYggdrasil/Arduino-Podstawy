#define Pot1 0 

 

void setup() { 

Serial.begin(9600); 

} 

 

void loop() { 

int PotValue; 

PotValue = analogRead(Pot1); 

Serial.print("Potencjometr: "); 

Serial.println(PotValue); 

delay(500); 

} 