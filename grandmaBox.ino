#include <Time.h>
#include <TimeLib.h>

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
int horaBox1[3],
    horaBox2[3],
    horaBox3[3],
    horaBox4[3],
    horaBox5[3],
    horaBox6[3];

SoftwareSerial bluetooth(pinoRX, pinoTX);

void setup() {
  bluetooth.begin(9600);
  Serial.begin(9600);
  pinMode(ledBox1, OUTPUT);
  pinMode(ledBox2, OUTPUT);
  pinMode(ledBox3, OUTPUT);
  pinMode(ledBox4, OUTPUT);
  pinMode(ledBox5, OUTPUT);
  pinMode(ledBox6, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(btnSentinel, INPUT_PULLUP);
  setTime(904200000);
}

void loop() {
  ConfBox();
  int hora = hour();
  int minuto = minute();
  if (hora == horaBox1[0] and minuto == horaBox1[1]) 
  {
    AletaLedBuzz(ledBox6);
  }
  if (hour() == horaBox2[0] and minute() == horaBox2[1]) AletaLedBuzz(ledBox2);
  if (hour() == horaBox3[0] and minute() == horaBox3[1]) AletaLedBuzz(ledBox3);
  if (hour() == horaBox4[0] and minute() == horaBox4[1]) AletaLedBuzz(ledBox4);
  if (hour() == horaBox5[0] and minute() == horaBox5[1]) AletaLedBuzz(ledBox5);
  if (hour() == horaBox6[0] and minute() == horaBox6[1]) AletaLedBuzz(ledBox6);
  HorarioDia();
}

//Junta os caracteres em uma string e o "*" indentifica o final da frase
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
//Pisca o led de uma determido led e o buzz
void AletaLedBuzz(int led)
{
  digitalWrite(led, 1);
  delay(300);
  digitalWrite(led, 0);
  delay(300); 
}
//Imprime hora e dia pela porta bluetooth
void HorarioDia()
{
  bluetooth.print(hour());
  bluetooth.print(':');
  bluetooth.print(minute());
  bluetooth.print(':');
  bluetooth.print(second());
  /*bluetooth.print(" ");
  bluetooth.print(day());
  bluetooth.print("/");
  bluetooth.print(month());
  bluetooth.print("/");
  bluetooth.println(year());*/
  delay(1000);
}
//Seta o horario do arduino
void SicronizaHorario(String mensagem)
{
  //mensagem.remove(0,1);
  setTime(HoraRemedio(mensagem), MinutoRemedio(mensagem), 0, 27, 8, 1998);
  //bluetooth.println(mensagem);
}
//Função que recebe uma string de hora(HH:MM) e retorna HH
int HoraRemedio(String mensagem)
{
  mensagem.remove(0,1);
  String hora;
  for (int i = 0; i < 2;i++)
  {
    hora.concat(mensagem[i]);
  }

  if (hora.length() == 2)
  {
  return hora.toInt();
  } else if (hora.length() == 1) {
    String c = hora;
    hora = "0";
    hora = hora.concat(c);
    return hora.toInt();
  }
}
//Função que recebe uma string de hora(HH:MM) e retorna MM
int MinutoRemedio(String mensagem)
{
  mensagem.remove(0,4);
  String minuto;
  for (int i = 0;i < 2;i++)
  {
    minuto.concat(mensagem[i]);
  }
  if (minuto.length() == 2)
  {
  return minuto.toInt();
  } else if (minuto.length() == 1) {
    String c = minuto;
    minuto = "0";
    minuto = minuto.concat(c);
    return minuto.toInt();
  }
}
//Configuração da Box
void ConfBox()
{
  if (bluetooth.available())
  {
    String mensagem;
    mensagem = MensagemSerial();
    if(mensagem.length() != 0)
    {
      //se a mensagem começa com '-' é pq o App que sicronizar o horario.
      if (mensagem[0] == '-')
      {
        SicronizaHorario(mensagem);
      }
      //Para configura a box1 a mensagem começa com '!'
      if (mensagem[0] == '!')
      {
        horaBox1[0] = HoraRemedio(mensagem);
        horaBox1[1] = MinutoRemedio(mensagem);
      }
      if (mensagem[0] == '@')
      {
        horaBox2[0] = HoraRemedio(mensagem);
        horaBox2[1] = MinutoRemedio(mensagem);
      }
      if (mensagem[0] == '#')
      {
        horaBox3[0] = HoraRemedio(mensagem);
        horaBox3[1] = MinutoRemedio(mensagem);
      }
      if (mensagem[0] == '$')
      {
        horaBox4[0] = HoraRemedio(mensagem);
        horaBox4[1] = MinutoRemedio(mensagem);
      }
      if (mensagem[0] == '%')
      {
        horaBox5[0] = HoraRemedio(mensagem);
        horaBox5[1] = MinutoRemedio(mensagem);
      }
      if (mensagem[0] == '&')
      {
        horaBox6[0] = HoraRemedio(mensagem);
        horaBox6[1] = MinutoRemedio(mensagem);
      }
      bluetooth.println("Horarios configurados!!");
    }    
  }
}

