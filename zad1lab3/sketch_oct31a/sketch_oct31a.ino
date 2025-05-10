#include <dht11.h>
#define DHT11PIN 4
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


dht11 DHT11;
int choice = 0;
void setup() {
  Serial.begin(9600);
  pinMode(13,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  lcd.init();  // inicjalizacja LCD
  lcd.backlight();
}


void loop() {

  int chk = DHT11.read(DHT11PIN);
  if(digitalRead(13) == LOW)
    choice = 1;
  if(digitalRead(12) == LOW)
    choice = 2;
  if(digitalRead(11) == LOW)
    choice = 3;
  lcd.scrollDisplayLeft();
  lcd.noBlink();
  Serial.println();
  switch(choice){
    case 1:
      Serial.print("Wilgotnosc (%): ");
      Serial.println((float)DHT11.humidity, 2);
      lcd.setCursor(0, 0);
      lcd.print("Wilgotnosc (%): ");
      lcd.print((float)DHT11.humidity);
      digitalWrite(7,HIGH);
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);
      if((float)DHT11.humidity<=33){
        digitalWrite(10,LOW);
        digitalWrite(9,LOW);
        digitalWrite(8,HIGH);
        }
    if((float)DHT11.humidity>33 && (float)DHT11.humidity<66){
        digitalWrite(10,LOW);
        digitalWrite(9,HIGH);
        digitalWrite(8,LOW);
        }
    if((float)DHT11.humidity>=66){
        digitalWrite(10,HIGH);
        digitalWrite(9,LOW);
        digitalWrite(8,LOW);
        }

    break;
    case 2:
      Serial.print("Temperatura  (C): ");
      Serial.println((float)DHT11.temperature, 2);
      lcd.setCursor(0, 0);
      lcd.print("Temperatura (C): ");
      lcd.print((float)DHT11.temperature, 2);
      digitalWrite(7,LOW);
      digitalWrite(6,HIGH);
      digitalWrite(5,LOW);
      if((float)DHT11.temperature<=5){
        digitalWrite(10,LOW);
        digitalWrite(9,LOW);
        digitalWrite(8,HIGH);
        }
    if((float)DHT11.temperature>5 && (float)DHT11.temperature<27){
        digitalWrite(10,LOW);
        digitalWrite(9,HIGH);
        digitalWrite(8,LOW);
        }
    if((float)DHT11.temperature>=27){
        digitalWrite(10,HIGH);
        digitalWrite(9,LOW);
        digitalWrite(8,LOW);
        }
    break;
    case 3:
      Serial.print("Temperatura  (F): ");
      float a = (1.8*((float)DHT11.temperature)+32) ;
      Serial.println((float)round(a), 2);
      lcd.setCursor(0, 0);
      lcd.print("Temperatura (F): ");
      lcd.print(a);
      digitalWrite(7,LOW);
      digitalWrite(6,LOW);
      digitalWrite(5,HIGH);
      if((float)a<=41){
        digitalWrite(10,LOW);
        digitalWrite(9,LOW);
        digitalWrite(8,HIGH);
        }
    if(a>41 && a<80.6){
        digitalWrite(10,LOW);
        digitalWrite(9,HIGH);
        digitalWrite(8,LOW);
        }
    if(a>=80.6){
        digitalWrite(10,HIGH);
        digitalWrite(9,LOW);
        digitalWrite(8,LOW);
        }
    break;

  }
  delay(500);
}
