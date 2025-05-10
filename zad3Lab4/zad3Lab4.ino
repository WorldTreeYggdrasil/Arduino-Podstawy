#define LATCH_DIO 4 

#define CLK_DIO 7 

#define DATA_DIO 8 

 

/* Segmentowane mapy bajtów dla liczb od 0 do 9 */ 

const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90,0x40}; 

/* Mapy bajtów umożliwiające wybranie cyfry od 1 do 4 */ 

const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8}; 

 

void setup () 

{ 



 pinMode(LATCH_DIO,OUTPUT); 

 pinMode(CLK_DIO,OUTPUT); 

 pinMode(DATA_DIO,OUTPUT); 

} 

 

/* Glowny program */ 

void loop() 

{ 

/* na wyświetlaczu pojawia się 3141 */ 

 WriteNumberToSegment(0 , 3); 

 WriteNumberToSegment(1 , 1); 

 WriteNumberToSegment(2 , 4); 

 WriteNumberToSegment(3 , 1); 

} 

 

/* Wpisz liczbę z zakresu od 0 do 9 do jednej z 4 cyfr wyświetlacza */ 

void WriteNumberToSegment(byte Segment, byte Value) 

{ 

 digitalWrite(LATCH_DIO,LOW); 

 shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]); 

 shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] ); 

 digitalWrite(LATCH_DIO,HIGH); 

} 