int odczytanaWartosc = 0; //Zmienna do przechowywania odczytu ADC 
int prog = 0;


void setup() { 

 pinMode(8, OUTPUT);

} 

 

void loop() { 

 odczytanaWartosc = analogRead(A5);//Odczytanie wartości z ADC 
 prog = analogRead(A4);
  

 if (odczytanaWartosc < prog ) { 

digitalWrite(8, HIGH);//Włączenie diody     

 } else { 

digitalWrite(8, LOW);//Wyłączenie diody       

 } 

  

 delay(50); 

} 