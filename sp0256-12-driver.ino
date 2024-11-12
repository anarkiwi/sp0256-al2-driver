#include "DigitalIO.h"

#define LRQ A0
#define SA8 A1
#define SA7 A2
#define SA3 2
#define SA2 3
#define SA1 4
#define SE 5
#define ALD 6
#define SA4 7
#define SA5 8
#define SA6 9
#define RESET 12
#define SBRS 10
#define SBY 11
#define TEST 13

DigitalPin<SA1> sa1;
DigitalPin<SA2> sa2;
DigitalPin<SA3> sa3;
DigitalPin<SA4> sa4;
DigitalPin<SA5> sa5;
DigitalPin<SA6> sa6;
DigitalPin<SA7> sa7;
DigitalPin<SA8> sa8;
DigitalPin<ALD> ald;
DigitalPin<LRQ> lrq;

void setup() {
  pinMode(SA1, OUTPUT);
  pinMode(SA2, OUTPUT);
  pinMode(SA3, OUTPUT);
  pinMode(SA4, OUTPUT);
  pinMode(SA5, OUTPUT);
  pinMode(SA6, OUTPUT);
  pinMode(SA7, OUTPUT);
  pinMode(SA8, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(SE, OUTPUT);
  pinMode(TEST, OUTPUT);
  pinMode(SBRS, OUTPUT);
  pinMode(ALD, OUTPUT);
  pinMode(LRQ, INPUT);
  pinMode(SBY, INPUT);
  digitalWrite(RESET, HIGH);
  digitalWrite(SE, HIGH);
  digitalWrite(TEST, LOW);
  digitalWrite(SBRS, HIGH);
  Serial.begin(115200);
}

#define WRITEBIT(a, b, p) p.write(a & 1<<b);

void write_addr(byte a) {
  WRITEBIT(a, 0, sa1);
  WRITEBIT(a, 1, sa2);
  WRITEBIT(a, 2, sa3);
  WRITEBIT(a, 3, sa4);
  WRITEBIT(a, 4, sa5);
  WRITEBIT(a, 5, sa6);
  WRITEBIT(a, 6, sa7);
  WRITEBIT(a, 7, sa8);
}

void speak(byte a) {
  while (lrq.read()) {};
  write_addr(a);
  ald.write(LOW);
  delay(1);
  ald.write(HIGH);
}

void loop() {
  while (Serial.available()) {
    byte b = Serial.read();
    speak(b);
    Serial.write(b);
    Serial.flush();
  }
}
