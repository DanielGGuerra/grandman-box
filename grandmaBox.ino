#include <SoftwareSerial.h>

const int pinoRX = 2;
const int pinoTX = 3;
const int box1 = 13;
const int box2 = 12;
const int box3 = 11;
const int box4 = 10;
const int box5 = 9;
const int box6 = 8;
const int buzzer = 7;
const int btnSentinel = 6;

SoftwareSerial bluetooth(pinoRX, pinoTX);

void setup() {
  // put your setup code here, to run once:
  bluetooth.begin(9600);
  pinMode(box1, OUTPUT);
  pinMode(box2, OUTPUT);
  pinMode(box3, OUTPUT);
  pinMode(box4, OUTPUT);
  pinMode(box5, OUTPUT);
  pinMode(box6, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(btnSentinel, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
