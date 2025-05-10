#define LATCH_DIO 4 
#define CLK_DIO 7 
#define DATA_DIO 8 
#define button1 A1
#define button2 A2
#define LM35 A4
#define Pot1 0

int val = 0; 
float temp = 0; 
int a=0;

/* Segmentowane mapy bajtów dla liczb od 0 do 9 */ 

const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90,0x40}; 

/* Mapy bajtów umożliwiające wybranie cyfry od 1 do 4 */ 

const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8}; 

unsigned int disbuff[] = { 0, 0, 0, 0 };
 

void setup () 

{ 
 pinMode(LATCH_DIO,OUTPUT); 

 pinMode(CLK_DIO,OUTPUT); 

 pinMode(DATA_DIO,OUTPUT);
 a=0;
 Serial.begin(9600); 
} 

 

/* Glowny program */ 

void loop() 

{ 
  val = analogRead(LM35);
  temp = ((val * 5.0) / 1024.0) * 100;
  int PotValue;
  PotValue = analogRead(Pot1);

if(digitalRead(button1)==LOW){
  a=1;}
if(digitalRead(button2)==LOW){
  a=2;}
/* na wyświetlaczu pojawia się 3141 */ 
if(a==1)
{
Serial.print("Temperatura = ");
Serial.println(temp);
Serial.println("\n");
Serial.println(disbuff[2]);
int temp1= temp*100;
disbuff[0] = temp1 / 1000;
disbuff[1] = temp1 % 1000 / 100;
disbuff[2] = temp1 % 100 / 10;
disbuff[3] = temp1 % 10;

}
if(a==2)
{
Serial.print("Potencjometr: ");
Serial.println(PotValue);

disbuff[0] = PotValue / 1000;
disbuff[1] = PotValue % 1000 / 100;
disbuff[2] = PotValue % 100 / 10;
disbuff[3] = PotValue % 10;
}

WriteNumberToSegment(0 , disbuff[0] ); 

WriteNumberToSegment(1 , disbuff[1]); 

WriteNumberToSegment(2 , disbuff[2]); 

WriteNumberToSegment(3 , disbuff[3]);
} 

 

/* Wpisz liczbę z zakresu od 0 do 9 do jednej z 4 cyfr wyświetlacza */ 

void WriteNumberToSegment(byte Segment, byte Value) 

{ 

 digitalWrite(LATCH_DIO,LOW); 

 shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]); 

 shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] ); 

 digitalWrite(LATCH_DIO,HIGH); 

} 