#include <dht11.h>
#define DHT11PIN 4
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int Trig = 2; 
int Echo = 3;
const int buzzer = 8;
int movement = 9;
int button = 10;

int CM;

long CZAS;

int lastButtonState;    // the previous state of button
int currentButtonState; // the current state of button

dht11 DHT11;
int choice = 0;
void setup() { 

 Serial.begin(9600);

 pinMode(Trig, OUTPUT);
 pinMode(buzzer, OUTPUT);
 pinMode(Echo, INPUT);
 pinMode(movement, INPUT);
 pinMode(button,INPUT_PULLUP);
 
  lcd.init();  // inicjalizacja LCD
  lcd.backlight();
 Serial.println("Test czujnika odleglosci"); 
} 

 

void loop() { 
  lcd.noBlink();
  int ruch = digitalRead(movement);
  int mode = digitalRead(button);
 pomiar_odleglosci(); 

 Serial.print("Odleglosc: ");
 Serial.print(CM); ;
 Serial.println(" cm\n"); 
 Serial.print("Ruch: ");
 Serial.print(ruch);
 Serial.print("\n");
 Serial.print("Button Mode: ");
 Serial.print(mode);
 if(CM>=50){
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Brak przeszkod");}
if(CM<50&&CM>=10){
lcd.setCursor(0, 0);
lcd.clear();
lcd.print("Uwaga");}
 if(CM<10){
lcd.setCursor(0, 0);
lcd.clear();
lcd.print("Zderzenie");
}

if(CM<10 && ruch==1&& mode== 1)
tone(buzzer, 1000);
if(CM<50&&CM>=10 && ruch==1&& mode== 1)
tone(buzzer, 500);
if(CM>=50 && ruch==1&& mode== 1)
tone(buzzer, 100);
if(ruch==0)
noTone(buzzer);
delay(200); 
} 

 

void pomiar_odleglosci() { 

 digitalWrite(Trig, LOW); 

 delayMicroseconds(2); 

 digitalWrite(Trig, HIGH); 

 delayMicroseconds(10); 

 digitalWrite(Trig, LOW); 

 digitalWrite(Echo, HIGH); 

 CZAS = pulseIn(Echo, HIGH); 

 CM = CZAS / 58;

} 