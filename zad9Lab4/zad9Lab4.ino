#define LM35 A4 

 

int val = 0;    

float temp = 0;  

 

void setup() { 

 Serial.begin(9600);  

} 

 

void loop() { 

 val = analogRead(LM35);  

 // odczytujemy wartość z portu analogowego A4 (J4) z czujnika analogowego temperatury LM35 

 temp = ((val * 5.0) / 1024.0) * 100;  

/* przeliczenie odczytanej wartości na napięcie w woltach (dla podłączenia pod 5 V) * 100 */ 

 

 Serial.print("Temperatura = "); 

 Serial.println(temp); // wyświetlamy wartość na serial monitorze 

 delay(1000);       

}