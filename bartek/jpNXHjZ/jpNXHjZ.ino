int latchPin = 4;
int clockPin = 7;
int dataPin = 8;

int KEY_C = A1;
int KEY_F = A2;
int KEY_W = A3;

unsigned char Dis_table[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0X80, 0X90 };

unsigned char Dis_buf[] = { 0xF1, 0xF2, 0xF4, 0xF8 };
unsigned char disbuff[] = { 0, 0, 0, 0 };

int Flag_up = 1;
int Flag_up1 = 1;
int Flag_up2 = 1;

#include <dht11.h> 

#define DHT11PIN A5 

dht11 DHT11; 

int czujnik = 5;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(czujnik, 5);

  pinMode(dataPin, OUTPUT);  //definicja PIN 4,7,8 jako OUTPUT wyjścia
  Serial.begin(9600);
}

void display() {

  for (char i = 0; i <= 3; i++) {
    digitalWrite(latchPin, LOW);
    if (disbuff[i] >= 10) {
      shiftOut(dataPin, clockPin, MSBFIRST, Dis_table[(disbuff[i] - 10)] & 0x7F);
    } else {
      shiftOut(dataPin, clockPin, MSBFIRST, Dis_table[disbuff[i]]);
    }

    shiftOut(dataPin, clockPin, MSBFIRST, Dis_buf[i]);

    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, 10);

    delay(2);
  }
}

void disableDisplay() {
    digitalWrite(latchPin, LOW);
    for (char i = 0; i <= 3; i++) {
      shiftOut(dataPin, clockPin, MSBFIRST, 0xFF);

    shiftOut(dataPin, clockPin, MSBFIRST, Dis_buf[i]);

    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, 10);

    delay(2);
    }
}

unsigned char ScanKey(){
  if (Flag_up && digitalRead(KEY_C) == LOW) {
    Flag_up = 0;

    if (digitalRead(KEY_C) == LOW) {
      return 1;
    }
  }
  if (digitalRead(KEY_C) == HIGH) {
    Flag_up = 1;
  }

  return 0;
}

unsigned char ScanKey1() {
  if (Flag_up1 && digitalRead(KEY_F) == LOW) {
    Flag_up1 = 0;

    if (digitalRead(KEY_F) == LOW) {
      return 1;
    }
  }

  if (digitalRead(KEY_F) == HIGH) {
    Flag_up1 = 1;
  }

  return 0;
}

unsigned char ScanKey2() {
  if (Flag_up2 && digitalRead(KEY_W) == LOW) {
    Flag_up2 = 0;

    if (digitalRead(KEY_W) == LOW) {
      return 1;
    }
  }

  if (digitalRead(KEY_W) == HIGH) {
    Flag_up2 = 1;
  }

  return 0;
}

int mode = 0;

int displayTime = 0;
int i = 0;
void loop() {
  if (displayTime > 0) {
    displayTime--;
    if (displayTime == 0) {
      disableDisplay();
    } else {
      display();
    }
   } 

  int modeChanged = 0;
  if (ScanKey() == 1) {
    mode = 0;
    modeChanged = 1;
  } else if (ScanKey1() == 1) {
    mode = 1;
    modeChanged = 1;
  } else if (ScanKey2() == 1) {
    mode = 2;
    modeChanged = 1;
  }

  int ruch = digitalRead(czujnik);
  if (ruch == HIGH) {
    displayTime = 200;
  }

  i++;
  if (i % 500 == 0 || modeChanged == 1) {
    int chk = DHT11.read(DHT11PIN); 
    Serial.print("Wilgotnosc (%): "); 
    Serial.println((float)DHT11.humidity, 2); 
    Serial.print("Temperatura (C): "); 
    Serial.println((float)DHT11.temperature, 2); 

    modeChanged = 0;
    if (mode == 0) {
      // C
      float temp = (float)DHT11.temperature;
      disbuff[0] = ((int)temp % 100 / 10);
      disbuff[1] = ((int)temp % 10) + 10;
      temp *= 100;
      disbuff[2] = ((int)temp % 100 / 10);
      disbuff[3] = ((int)temp % 10);
    } else if (mode == 1) {
      // F
      float temp = (float)DHT11.temperature;
      temp = (temp * 2) + 30;
      disbuff[0] = ((int)temp % 100 / 10);
      disbuff[1] = ((int)temp % 10) + 10;
      temp *= 100;
      disbuff[2] = ((int)temp % 100 / 10);
      disbuff[3] = ((int)temp % 10);
    } else {
      // wilg
      float h = (float)DHT11.humidity;
      disbuff[0] = ((int)h % 100 / 10);
      disbuff[1] = ((int)h % 10) + 10;
      h *= 100;
      disbuff[2] = ((int)h % 100 / 10);
      disbuff[3] = ((int)h % 10);
    }
  }
  delay(1);
}