#include <math.h>
int latchPin = 4;
int clockPin = 7;
int dataPin = 8;
int KEY_ADD = A1; //Przycisk A1 dodawanie 
int KEY_DEC = A2; //Przycisk A2 odejmowanie
unsigned char Dis_table[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 
0X80, 0X90 };
/* Ta tabela definiuje 7 segmentów wyświetlacza, 0x nie jest tutaj używane.
00 = wszystkie segmenty włączone, FF = wszystkie segmenty wyłączone, 0x7F jest 
używane jako kropka dziesiętna */
unsigned char Dis_buf[] = { 0xF1, 0xF2, 0xF4, 0xF8 };
// ta tabela ustawia „selektor” wybranej cyfry
unsigned char disbuff[] = { 0, 0, 0, 0 };
// ustaw bufor wyświetlania na 0
int SUM = 0;
int Flag_up = 1;
int Flag_up1 = 1;

#define Pot1 0
#define LM35 A4
int val = 0; 
float temp = 0; 
int a = 0;

void setup() {
pinMode(latchPin, OUTPUT);
pinMode(clockPin, OUTPUT);
pinMode(dataPin, OUTPUT); //definicja PIN 4,7,8 jako OUTPUT wyjścia
Serial.begin(9600);

}
void display() {
for (char i = 0; i <= 3; i++) {
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, Dis_table[disbuff[i]]);
//Wysłanie wartosci do wyswietlacza
shiftOut(dataPin, clockPin, MSBFIRST, Dis_buf[i]);
digitalWrite(latchPin, HIGH);
delay(2);
/* poczekaj 2 ms przed przejściem do następnego ekranu, spróbuj innej wartości 
(na przykład 100 ), aby zobaczyć, jak działa multipleksowanie */
}
}
unsigned char ScanKey() //Przycisk A1 (S1)
{
if (Flag_up && digitalRead(KEY_ADD) == LOW) {
Flag_up = 0;
display();
display();
if (digitalRead(KEY_ADD) == LOW) {
return 1;
}
}
if (digitalRead(KEY_ADD) == HIGH) {
Flag_up = 1;
}
return 0;
}
unsigned char ScanKey1() //Przycisk A2 (S2)
{
if (Flag_up1 && digitalRead(KEY_DEC) == LOW) {
Flag_up1 = 0;
display();
display();
if (digitalRead(KEY_DEC) == LOW) {
return 1;
}
}
if (digitalRead(KEY_DEC) == HIGH) {
Flag_up1 = 1;
}
return 0;
}
void loop() {
display();
int PotValue;
PotValue = analogRead(Pot1);
val = analogRead(LM35); 
temp = ((val * 5.0) / 1024.0) * 100;

if (ScanKey() == 1) // jeżeli przycisk A1 jest wciśniety to
{
Serial.print("Potencjometr: ");
Serial.println(PotValue);
disbuff[0] = PotValue / 1000; // Wypełnij 4 bufory wyświetlania nową wartością
disbuff[1] = PotValue % 1000 / 100;
disbuff[2] = PotValue % 100 / 10;
disbuff[3] = PotValue % 10;
}

if (ScanKey1() == 1) // jeżeli przycisk A2 jest wciśniety to
{
Serial.print("Temperatura = ");
Serial.println(temp); 
int temp1=temp*100;
disbuff[0] = temp1 / 1000; // Wypełnij 4 bufory wyświetlania nową wartością
disbuff[1] = temp1 % 1000 / 100;
disbuff[2] = temp1 % 100 / 10;
disbuff[3] = temp1 % 10;

}
}