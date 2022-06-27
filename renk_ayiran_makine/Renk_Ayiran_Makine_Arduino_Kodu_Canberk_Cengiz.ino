#include<Servo.h>

//TCS 3200 pin tanimlari
#define s0 2 //S0 > Arduino pin#2 
#define s1 3 //S1 > Arduino pin#3 
#define s2 4 //S2 > Arduino pin#4 
#define s3 5 //S3  > Arduino pin#5
#define sensorOut 6 //Output  > Arduino pin#6 


//sensorOut verisini kaydetmek için değişken
int frequency = 0;

// rengi kaydetmek için değişken
byte AlgilananRenk = 0;

//Servo Tanimlama

Servo Besleyici_Servo;
Servo Karar_Verici_Servo;

//Gecikme tanimlama
byte kisa_gecikme_ms = 5;
byte orta_gecikme_ms = 30;
byte uzun_gecikme_ms = 1000;
byte cokuzun_gecikme_ms = 2000;

//Besleyici Servo Konum
byte pos1Besleyici_Servo = 165;
byte pos2Besleyici_Servo = 92;
byte pos3Besleyici_Servo = 0;

//Karar_Verici_Servo Konum
byte Karar_Verici_Servo_Kirmizi = 16;
byte Karar_Verici_Servo_Turuncu = 48;
byte Karar_Verici_Servo_Yesil = 80;
byte Karar_Verici_Servo_Sari = 120;
byte Karar_Verici_Servo_Mor = 153;


void setup() {

  //TCS 3200 Pin Ayarlama
  pinMode (s0, OUTPUT);
  pinMode (s1, OUTPUT);
  pinMode (s2, OUTPUT);
  pinMode (s3, OUTPUT);
  pinMode (sensorOut, INPUT);

  //Sensör Frekans Ölçek Ayari - 100%
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);

  //Servo Pin Atama
  Besleyici_Servo.attach (9);
  Karar_Verici_Servo.attach(11);
  
  //Saniyedeki bayt cinsinden iletişim
  Serial.begin(9600);

}

void loop() {
  
  //Pozisyon 1 den Pozisyon 2 ye geçiş
  for (int i = pos1Besleyici_Servo; i > pos2Besleyici_Servo ; i--) {

    Besleyici_Servo.write (i);
    delay (orta_gecikme_ms);
  }
  
  //Sensör Altinda Bekleme
  delay(uzun_gecikme_ms);

  //Renk Okuma Fonksiyonu
  AlgilananRenk = Renk_Tara();

  //Sensörde Okunan Renge Göre Case Secimi
  switch (AlgilananRenk) {

    // Kirmizi
    case 1:
      Karar_Verici_Servo.write (Karar_Verici_Servo_Kirmizi);
      break;

    //Turuncu
    case 2:
      Karar_Verici_Servo.write (Karar_Verici_Servo_Turuncu);
      break;

    //Yesil
    case 3:
      Karar_Verici_Servo.write (Karar_Verici_Servo_Yesil);
      break;

    //Sari
    case 4:
      Karar_Verici_Servo.write (Karar_Verici_Servo_Sari);
      break;

    //Mor
    case 5:
      Karar_Verici_Servo.write (Karar_Verici_Servo_Mor);
      break;

  }

  //Düşme Pozisyonu Gecikmesi
  delay(uzun_gecikme_ms);


  //Besleyici Servo Pozisyon 2 den Pozisyon 3 ye (Düşme Pozisyonu) İlerlemesi
  for (int i = pos2Besleyici_Servo; i > pos3Besleyici_Servo; i--) {

    Besleyici_Servo.write (i);
    delay (orta_gecikme_ms);

  }

  //Servo Dönüş Gecikmesi
  delay(uzun_gecikme_ms);


  //Besleme Servosu Pozisyon 1 e Dönüşü
  for (int i = pos3Besleyici_Servo; i < pos1Besleyici_Servo ; i++) {

    Besleyici_Servo.write (i);
    delay (kisa_gecikme_ms);
  }


  //Okunan Renk Sifirlama
  AlgilananRenk= 0;

  //Başlama için Gecikme
  delay (cokuzun_gecikme_ms);

}

int Renk_Tara() {


  //---Kirmizi Renk Okuma... S2 LOW - S3 LOW---
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  frequency = pulseIn(sensorOut, LOW);

  int Kirmizivalue = frequency;

  Serial.print("R=");
  Serial.print(Kirmizivalue);
  Serial.print("  ");

  delay(50);

  //---Yesil Renk Okuma ... S2 LOW - S3 HIGH---
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  frequency = pulseIn(sensorOut, LOW);

  int YesilValue = frequency;

  Serial.print("G=");
  Serial.print(YesilValue);
  Serial.print("  ");

  delay(50);


  //---Mavi Renk Okuma ... S2 HIGH - S3 LOW---
  digitalWrite(s2, HIGH);
  digitalWrite(s3, LOW);
  frequency = pulseIn(sensorOut, LOW);

  int MaviValue = frequency ;

  Serial.print("B=");
  Serial.print(MaviValue);
  Serial.print("  ");

  delay(50);


  //---Clear Value Okuma ... S2 HIGH - S3 HIGH---
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  frequency = pulseIn(sensorOut, LOW);

  int clearValue = frequency ;

  Serial.print("C=");
  Serial.print(clearValue);
  Serial.println("  ");

  delay(50);


  //////////Kirmizi Renk Şartlari/////////
  if (Kirmizivalue>45 & Kirmizivalue>=40 & clearValue<65 & clearValue>=55) {
    AlgilananRenk= 1; // Kirmizi  
  }

  //////////Turuncu Renk Şartlari////////
  if (Kirmizivalue<39 & Kirmizivalue>14 & clearValue<70 & clearValue>=45 ) {
    AlgilananRenk= 2; // Turuncu
  }

  //////////Yesil Renk Şartlari/////////
  if (MaviValue<18 & MaviValue>4 & clearValue<48 & clearValue>20 ) {
    AlgilananRenk= 3; // Yesil
  }

  //////////Sari Renk Şartlari/////////
  if (Kirmizivalue<32 & Kirmizivalue>8 & clearValue<=37 & clearValue>10 ) {
    AlgilananRenk= 4; // Sari }
  }

  //////////Mor Renk Şartlari//////////
  if ( Kirmizivalue<=63 & Kirmizivalue>=48 & clearValue<74 & clearValue>=54) {
    AlgilananRenk= 5; // Mor
  }

  //--- Bulunan Renge Donme---
  return AlgilananRenk;
}
