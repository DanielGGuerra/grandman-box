#include <TimeAlarms.h>

#include <Time.h>

#include <SoftwareSerial.h>

const int pinoRX = 0;
const int pinoTX = 1;
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
  if (bluetooth.available() > 0){
    String textRec = leString();
    if (leString().length() == 8){
      //setTime
    }
  } 
}

//Funçoes
String leString(){
  String conteudo = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(bluetooth.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
    
  Serial.print("Recebi: ");
  Serial.println(conteudo);
    
  return conteudo;
}


