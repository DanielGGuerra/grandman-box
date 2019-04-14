#include <TimeAlarms.h>
#include <Time.h>
#include <SoftwareSerial.h>

const int pinoRX = 3;
const int pinoTX = 2;
const int ledBox1 = 13;
const int ledBox2 = 12;
const int ledBox3 = 11;
const int ledBox4 = 10;
const int ledBox5 = 9;
const int ledBox6 = 8;
const int buzzer = 7;
const int btnSentinel = 6;

time_t horaBox1;

SoftwareSerial bluetooth(pinoRX, pinoTX);

void setup() {
  // put your setup code here, to run once:
  bluetooth.begin(9600);
  pinMode(ledBox1, OUTPUT);
  pinMode(ledBox2, OUTPUT);
  pinMode(ledBox3, OUTPUT);
  pinMode(ledBox4, OUTPUT);
  pinMode(ledBox5, OUTPUT);
  pinMode(ledBox6, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(btnSentinel, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (bluetooth.available())
  {
    String mensagem;
    mensagem = MensagemSerial();
    if(mensagem.length() != 0)
    {
      //se a mensagem começa com '-' é pq o App que cronizar o horario.
      if (mensagem[0] == '-')
      {
        SicronizaHorario(mensagem);
      }
      //configurando o horario da box1
      /*if (mensagem[0] == '!')
      {
         
      }*/
    }
  }
  HorarioDia();  
}

//Funçoes

String MensagemSerial()
{
  char p;

  String palavra;

  while(bluetooth.available() > 0)
  {
    p = (byte)bluetooth.read();
  
      if(p == '*')
      {
        break;
      }else{
        palavra += p;  
      }
      delay(10);
  }
  return palavra;
}

void AletaLed(int led)
{//for é apanas para teste.
  for (int i; i < 20;i++)
  {
    digitalWrite(led, 1);
    delay(300);
    digitalWrite(led, 0);
    delay(300);
  }
}

void HorarioDia()
{
  bluetooth.print(hour());
  bluetooth.print(':');
  bluetooth.print(minute());
  bluetooth.print(':');
  bluetooth.print(second());
  bluetooth.print(" ");
  bluetooth.print(day());
  bluetooth.print("/");
  bluetooth.print(month());
  bluetooth.print("/");
  bluetooth.println(year());
  delay(1000);
}

void SicronizaHorario(String mensagem)
{
  mensagem.remove(0,1);
  setTime(mensagem.toInt() - 10800);
  bluetooth.println(mensagem);
}


