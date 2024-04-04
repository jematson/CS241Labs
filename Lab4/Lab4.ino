#include "benchmark.h" //<- Dr. Lawlor's code

void setup() {
  Serial.begin(57600);
  Serial.println("Starting benchmarks...");
}

// Define functions to be benchmarked.
//  These need to take int and return int.
int addInt(int v) {
  int i=3;
  return v+i;
}
int empty(int v) {
  return 0;
}
int andInt(int v) {
  int i=3;
  return v&i;
}
int shift1int(int v) {
  return v<<1;
}
int shift4int(int v) {
  return v<<4;
}
int mulInt(int v) {
  int i = 5;
  return v*i;
}
int divInt(int v) {
  int i = 5;
  return i/v;
}
int addFloat(int v) {
  float i = 2.5;
  return v+i;
}
int serialPrint (int v) {
  Serial.print((char)0);
}

int digitalWrite1(int v) {
  digitalWrite(8, 0);
  return 0;
}
int digitalWrite6(int v) {
  digitalWrite(8, 0);
  digitalWrite(9, 0);
  digitalWrite(10, 0);
  digitalWrite(11, 0);
  digitalWrite(12, 0);
  digitalWrite(13, 0);
  return 0;
}
const int pinTable[6]= {8, 9, 10, 11, 12, 13};
int digitalWrite6Table(int v) {
  
  for(int pin : pinTable)
    digitalWrite(pin,0);
  return 0;
}
int digitalWritePORT(int v) {
  PORTB = 0b00000000;
  return 0;
}
int digitalRead1(int v) {
  digitalRead(8);
  return 0;
}
int digitalReadPORT(int v) {
  return PINB;
}
int analogRead1(int v) {
  analogRead(A0);
  return 0;
}

int callMicros(int v) {
  micros();
  return 0;
}
int delayMicroseconds1(int v) {
  delayMicroseconds(1);
  return 0;
}
int delayMicroseconds10(int v) {
  delayMicroseconds(10);
  return 0;
}
int delay1(int v) {
  delay(1);
  return 0;
}

void loop() {
  // Call benchmark on each of our functions
  benchmark("addInt     ",addInt,1000);
  benchmark("empty      ",empty,1000);
  benchmark("andIt      ",andInt, 1000);
  benchmark("shift1int  ",shift1int,1000);
  benchmark("shift4int  ",shift4int,1000);
  benchmark("mulInt     ",mulInt,1000);
  benchmark("divInt     ",divInt,1000);
  benchmark("addFloat   ",addFloat,1000);
  benchmark("serialPrint",serialPrint,1000);
  benchmark("digitalWrite1     ",digitalWrite,1000);
  benchmark("digitalWrite6     ",digitalWrite6,1000);
  benchmark("digitalWrite6Table",digitalWrite6Table,1000);
  benchmark("digitalWritePORT  ",digitalWritePORT,1000);
  benchmark("digitalRead1      ",digitalRead1,1000);
  benchmark("digitalReadPORT   ",digitalReadPORT,1000);
  benchmark("analogRead1       ",analogRead1,1000);
  benchmark("callMicros         ",callMicros,1000);
  benchmark("delayMicroseconds1 ",delayMicroseconds1,1000);
  benchmark("delayMicroseconds10",delayMicroseconds10,1000);
  benchmark("delay1             ",delay1,1000);
  
  // Blank line and let us read the results before retest
  Serial.println();
  delay(8000);
}
