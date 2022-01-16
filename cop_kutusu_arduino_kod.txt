#include<Servo.h>    //servo kütüphanesini ekledik

Servo servomuz;    //servomuz

const int eko=9;         //eko pinini tanımladık

const int trig=8;        //trig pinini tanımladık

int mesafe;

int sure;

void setup() {

  servomuz.attach(10);   //servo motorun 10 numaralı pine tanımladık

  pinMode(trig,OUTPUT);  // trig pinini çıkış olarak tanımladık

  pinMode(eko,INPUT);    // echo pinini giriş olarak tanımladık

  Serial.begin(9600);

}    

void loop() {

  digitalWrite(eko, LOW); //sensör pasif hale getirildi

  delayMicroseconds(5);

  digitalWrite(trig, HIGH); //Sensore ses dalgasının üretmesi için emir verildi

  delayMicroseconds(10);

  digitalWrite(trig, LOW); //Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi

sure = pulseIn(eko, HIGH); //ses dalgasının geri dönmesi için geçen sure ölçülüyor

  mesafe = sure / 29.1 / 2;

   if (mesafe<40 )

{

    servomuz.write(175); // servoyu 175 derece açısına getirdik

    Serial.println(mesafe);  //mesaye değerini seri ekrana yazdırdık

    Serial.println("-acikk-");  //serial ekrandan okuduk

    delay(3000) ;  // 3 saniye bekle

  }

  else

  {

    servomuz.write(70); // servoyu 70 derece açısına getirdik.

    Serial.println(mesafe);

    Serial.println("-kapali-"); //serial ekrandan okuduk

  }

}