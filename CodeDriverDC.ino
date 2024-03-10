#include "RPi_Pico_TimerInterrupt.h"
#include "DongCoPi.h"
#include <arduino.h>

#define pinPwm1 3
#define pinDir1 2
#define pinPwm2 5
#define pinDir2 4
#define pinPwm3 7
#define pinDir3 6
#define pinPwm4 9
#define pinDir4 8
#define pinDebug 25

RPI_PICO_Timer DongCo1(0);
RPI_PICO_Timer DongCo2(1);
RPI_PICO_Timer DongCo3(2);
RPI_PICO_Timer DongCo4(3);
unsigned int timerXung = maxTimer;
unsigned long xung1, xung2, xung3, xung4, startXung, x, dem;
unsigned long int timerdelay = millis();
bool Dir1, Dir2, Dir3, Dir4, isFree;
unsigned int m, n, s;
unsigned int xungTangtoc[100];
unsigned int xungGiamtoc[100];
char giaotiep[5];
void setup()
{

  Serial.begin(115200);
  Serial.println(F("SETUPPPP"));
  Serial1.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pinPwm1, OUTPUT);
  pinMode(pinDir1, OUTPUT);
  pinMode(pinPwm2, OUTPUT);
  pinMode(pinDir2, OUTPUT);
  pinMode(pinPwm3, OUTPUT);
  pinMode(pinDir3, OUTPUT);
  pinMode(pinPwm4, OUTPUT);
  pinMode(pinDir4, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);
  isFree == true;
  delay(2000);

  Serial.print("TimeTangToc = " + String(timeTangoc));
  Serial.print("  SoLanTangToc = " + String(soLantang));
  Serial.println("  Time1LanTang = " + String(time1lantang));

  Serial.println();
  // ITimer1.stopTimer();
  // ITimer0.restartTimer();

  // tien(10000);
  // while (xung1 > 0 || xung2 > 0 || xung3 > 0 || xung4 > 0) {
  //   Serial.println("Time = " + String(timerXung) + " xung = " + String(xung1));
  //   delay(500);
  // }
  // phai(6000);
  // while (xung1 > 0 || xung2 > 0 || xung3 > 0 || xung4 > 0) {
  //   Serial.println("Time = " + String(timerXung) + " xung = " + String(xung1));
  //   delay(500);
  // }
  // tien(5700);
  // while (xung1 > 0 || xung2 > 0 || xung3 > 0 || xung4 > 0) {
  //   Serial.println("Time = " + String(timerXung) + " xung = " + String(xung1));
  //   delay(500);
  // }
  // trai(3000);
  // while (xung1 > 0 || xung2 > 0 || xung3 > 0 || xung4 > 0) {
  //   Serial.println("Time = " + String(timerXung) + " xung = " + String(xung1));
  //   delay(500);
  // }
  // xoaytrai(90);
}
void loop()
{
  if (Serial1.available() > 0)
  {
    giaotiep[0] = Serial1.readByte();
    if (giaotiep[0] == START_BYTE)
    {
      for (int i = 1; i < 5; i++)
      {
        giaotiep[i] = Serial1.readByte();
      }
    }
    if (giaotiep[0] == START_BYTE && giaotiep[4] == STOP_BYTE)
    { // check
      unsigned int value = giaotiep[2] * 256 + giaotiep[3];
      control(giaotiep[1], value);
    }
  }
}
void control(char lenh, unsigned int value)
{
  switch (lenh)
  {
  case PAUSE: // stop but no clear
    break;
  case RESUME: // resume
    break;
  case STOP: // stop and clear pulls
    break;
  case LEFT: trai(value);
    break;
  case RIGHT: phai(value);
    break;
  case UP: tien(value);
    break;
  case DOWN: lui(value);
    break;
  case UP_LATE:
    break;
  case DOWN_LATE:
    break;
  case LEFT_LATE:
    break;
  case RIGHT_LATE:
    break;
  case RO_LEFT:
    break;
  case RO_RIGHT:
    break;
  }
}
void xoaytrai(unsigned long goc)
{
  // isFree=false;
  setDir(false, false, false, false); // tien
  unsigned long xung = (goc * ppr) / 360;
  startXung = xung;
  xung1 = xung - (xung * 6) / 100;
  xung2 = xung + (xung * 2) / 100;
  xung3 = xung - (xung * 8) / 100;
  xung4 = xung + (xung * 2) / 100;

  xungTangtoc[0] = startXung;
  s = 0;
  for (int i = 1; i < soLantang + 1; i++)
  {
    s += (timeTangoc / soLantang) * 1000 / (maxTimer - (i - 1) * ((maxTimer - minTimer) / soLantang));
    xungTangtoc[i] = startXung - s;
    Serial.print(" " + String(xungTangtoc[i]));
  }
  Serial.println();
  // xungTangtoc[0]=startXung;
  s = 0;
  for (int i = 0; i < soLantang + 1; i++)
  {
    s += (timeTangoc / soLantang) * 1000 / (maxTimer - i * ((maxTimer - minTimer) / soLantang));
    xungGiamtoc[i] = s;
    Serial.print(" " + String(xungGiamtoc[i]));
  }

  setTimer(timerXung);
}
void xoayphai(unsigned long goc)
{
  // isFree=false;
  setDir(true, true, true, true); // tien
  unsigned long xung = (goc * ppr) / 360;
  startXung = xung;
  xung1 = xung - (xung * 6) / 100;
  xung2 = xung + (xung * 2) / 100;
  xung3 = xung - (xung * 8) / 100;
  xung4 = xung + (xung * 2) / 100;

  xungTangtoc[0] = startXung;
  s = 0;
  for (int i = 1; i < soLantang + 1; i++)
  {
    s += (timeTangoc / soLantang) * 1000 / (maxTimer - (i - 1) * ((maxTimer - minTimer) / soLantang));
    xungTangtoc[i] = startXung - s;
    Serial.print(" " + String(xungTangtoc[i]));
  }
  Serial.println();
  // xungTangtoc[0]=startXung;
  s = 0;
  for (int i = 0; i < soLantang + 1; i++)
  {
    s += (timeTangoc / soLantang) * 1000 / (maxTimer - i * ((maxTimer - minTimer) / soLantang));
    xungGiamtoc[i] = s;
    Serial.print(" " + String(xungGiamtoc[i]));
  }

  setTimer(timerXung);
}
void tien(unsigned long xung)
{
  isFree = false;
  setDir(false, true, true, false); // tien

  startXung = xung;
  xung1 = xung - (xung * 6) / 100;
  xung2 = xung + (xung * 2) / 100;
  xung3 = xung - (xung * 8) / 100;
  xung4 = xung + (xung * 2) / 100;

  xungTangtoc[0] = startXung;
  s = 0;
  for (int i = 1; i < soLantang + 1; i++)
  {
    s += (timeTangoc / soLantang) * 1000 / (maxTimer - (i - 1) * ((maxTimer - minTimer) / soLantang));
    xungTangtoc[i] = startXung - s;
    Serial.print(" " + String(xungTangtoc[i]));
  }
  Serial.println();
  // xungTangtoc[0]=startXung;
  s = 0;
  for (int i = 0; i < soLantang + 1; i++)
  {
    s += (timeTangoc / soLantang) * 1000 / (maxTimer - i * ((maxTimer - minTimer) / soLantang));
    xungGiamtoc[i] = s;
    Serial.print(" " + String(xungGiamtoc[i]));
  }

  setTimer(timerXung);
}
void trai(unsigned long xung)
{
  setDir(true, true, false, false); // phai
  startXung = xung;
  xung1 = xung - (xung * 2) / 100;
  xung2 = xung - (xung * 5) / 100;
  xung3 = xung + (xung * 5) / 100;
  xung4 = xung; // + (xung*7)/100;

  xungTangtoc[0] = startXung;
  s = 0;
  for (int i = 1; i < soLantang + 1; i++)
  {
    s += (timeTangoc / soLantang) * 1000 / (maxTimer - (i - 1) * ((maxTimer - minTimer) / soLantang));
    xungTangtoc[i] = startXung - s;
    Serial.print(" " + String(xungTangtoc[i]));
  }
  Serial.println();
  // xungTangtoc[0]=startXung;
  s = 0;
  for (int i = 0; i < soLantang + 1; i++)
  {
    s += (timeTangoc / soLantang) * 1000 / (maxTimer - i * ((maxTimer - minTimer) / soLantang));
    xungGiamtoc[i] = s;
    Serial.print(" " + String(xungGiamtoc[i]));
  }

  setTimer(timerXung);
}
void phai(unsigned long xung)
{
  setDir(false, false, true, true); // phai
  startXung = xung;
  xung1 = xung - (xung * 9) / 100;
  xung2 = xung; // + (xung*2)/100;
  xung3 = xung; // - (xung*11)/100;
  xung4 = xung + (xung * 7) / 100;

  xungTangtoc[0] = startXung;
  s = 0;
  for (int i = 1; i < soLantang + 1; i++)
  {
    s += (timeTangoc / soLantang) * 1000 / (maxTimer - (i - 1) * ((maxTimer - minTimer) / soLantang));
    xungTangtoc[i] = startXung - s;
    Serial.print(" " + String(xungTangtoc[i]));
  }
  Serial.println();
  // xungTangtoc[0]=startXung;
  s = 0;
  for (int i = 0; i < soLantang + 1; i++)
  {
    s += (timeTangoc / soLantang) * 1000 / (maxTimer - i * ((maxTimer - minTimer) / soLantang));
    xungGiamtoc[i] = s;
    Serial.print(" " + String(xungGiamtoc[i]));
  }

  setTimer(timerXung);
}
bool xungDc1(struct repeating_timer *t)
{
  if (xung1 > 0)
  {
    tangGiamtoc(xung1);
    digitalWrite(pinPwm1, !digitalRead(pinPwm1));
    xung1--;
  }
  else
  {
    DongCo1.stopTimer();
    if (xung1 == 0 && xung2 == 0 && xung3 == 0 && xung4 == 0)
    {
      isFree = true;
    }
  }
  return true;
}
bool xungDc2(struct repeating_timer *t)
{
  if (xung2 > 0)
  {
    digitalWrite(pinPwm2, !digitalRead(pinPwm2));
    xung2--;
  }
  else
  {
    DongCo2.stopTimer();
    if (xung1 == 0 && xung2 == 0 && xung3 == 0 && xung4 == 0)
    {
      isFree = true;
    }
  }
  return true;
}
bool xungDc3(struct repeating_timer *t)
{
  if (xung3 > 0)
  {
    digitalWrite(pinPwm3, !digitalRead(pinPwm3));
    xung3--;
  }
  else
  {
    DongCo3.stopTimer();
    if (xung1 == 0 && xung2 == 0 && xung3 == 0 && xung4 == 0)
    {
      isFree = true;
    }
  }
  return true;
}
bool xungDc4(struct repeating_timer *t)
{
  if (xung4 > 0)
  {
    digitalWrite(pinPwm4, !digitalRead(pinPwm4));
    xung4--;
  }
  else
  {
    DongCo4.stopTimer();
    if (xung1 == 0 && xung2 == 0 && xung3 == 0 && xung4 == 0)
    {
      isFree = true;
    }
  }

  return true;
}
void setDir(bool vdir1, bool vdir2, bool vdir3, bool vdir4)
{
  digitalWrite(pinDir1, vdir1);
  digitalWrite(pinDir2, vdir2);
  digitalWrite(pinDir3, vdir3);
  digitalWrite(pinDir4, vdir4);
}
void setTimer(unsigned int pullTime)
{
  timerXung = pullTime;
  DongCo2.attachInterruptInterval((pullTime * xung1) / xung2, xungDc2);
  DongCo3.attachInterruptInterval((pullTime * xung1) / xung3, xungDc3);
  DongCo4.attachInterruptInterval((pullTime * xung1) / xung4, xungDc4);
  DongCo1.attachInterruptInterval(pullTime, xungDc1);
}
void tangGiamtoc(unsigned long T1)
{
  if (T1 > startXung / 2)
  {
    for (int i = 0; i < soLantang + 1; i++)
    {
      if (T1 == xungTangtoc[i])
      {
        setTimer(maxTimer - i * ((maxTimer - minTimer) / soLantang));
      }
    }
  }
  else
  {
    for (int i = 0; i < soLantang + 1; i++)
    {
      if (T1 == xungGiamtoc[i])
      {
        setTimer(minTimer + (soLantang - i) * ((maxTimer - minTimer) / soLantang));
      }
    }
  }
}
int getDirec()
{
  SerialDirec.print("a");
  String m = SerialDirec.readString();
  int huongRt = m.substring(m.indexOf('a') + 1, m.indexOf('b')).toInt();
  return huongRt;
}