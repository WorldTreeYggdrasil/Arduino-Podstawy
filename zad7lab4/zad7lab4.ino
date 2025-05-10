int potpin = A0; 

int ledpin1 = 11; 

int ledpin2 = 10;

int val = 0;

void setup() { 

 Serial.begin(9600);  

} 

void loop() { 

 val = analogRead(potpin); 

 Serial.print("Val: "); 

 Serial.println(val);

 analogWrite(ledpin1, val / 4); 

/*zapisujemy wartośc analogową PWM (wartośc moze być od 0 do 255,dlatego dzielimy przez 4) */ 

 analogWrite(ledpin2, 255);

 delay(100);

} 