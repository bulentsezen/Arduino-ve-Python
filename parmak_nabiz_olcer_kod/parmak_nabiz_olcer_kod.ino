#include <LCD5110_Basic.h>                    //5110 ekranımız için gerekli kütüphaneyi ekliyoruz.
LCD5110 myGLCD(8, 9, 10, 11, 12);             //Ekran objemizi (myGLCD) bağlamış olduğumuz pinleri belirterek oluşturuyoruz
#define USE_ARDUINO_INTERRUPTS true           //Pulse kütüphanesinin daha doğru ölçüm yapabilmesi için bu ayarı etkinleştiriyoruz
#include <PulseSensorPlayground.h>            //Bilgisayarımıza kurmuş olduğumuz Pulse Playground kütüphanesini ekliyoruz.

int nabiz;                                    //İçinde dakikadaki nabzı tutacağımız değişkeni oluşturuyoruz.
int lcd_ledi = 6;                             //5110 ekranımızın arka plan aydınlatmasının bağlı olduğu pini belirliyoruz.

extern uint8_t SmallFont[];                   //5110 ekranımızda yazacağımız yazı için gerekli fontları ekliyoruz.
extern uint8_t BigNumbers[];                  
const int PulseWire = 0;                      //Pulse sensörümüzü bağlamış olduğumuz Analog pinini belirliyoruz (A0).
const int LED13 = 13;                         // Arduino üzerindeki ledin nabzımızla birlikte yanıp sönmesi için bu değişkeni 13 numaralı pin olarak ayarlıyoruz.
int Threshold = 520;                          //Belirlemiş olduğumuz eşik değerini bu değişkene atıyoruz.
PulseSensorPlayground pulseSensor;            //Sensörümüzü kodumuzda kullanabilmek için onu obje olarak (pulseSensor) oluşturuyoruz.

void setup() {
  Serial.begin(9600);                         //Bilgisayrımızla olan seri iletişimi başlatıyoruz.
  pulseSensor.analogInput(PulseWire);         //Pulse sensörünün bağlı olduğu pini belirliyoruz.
  pulseSensor.blinkOnPulse(LED13);            //arduino üzerindeki ledin nabzımızla yanıp sönmesini istediğimizi söylüyoruz.
  pulseSensor.setThreshold(Threshold);        //Değişkene atamış olduğumuz eşik değerini uyguluyoruz.
  digitalWrite(lcd_ledi, HIGH);               //5110 ekranın arka plan aydınlatmasına güç veriyoruz.
  myGLCD.InitLCD();                           //5110 ekranımızı başlatıyoruz.
  myGLCD.setContrast(60);                     //5110 ekranımızın kontrastını belirliyoruz.
  myGLCD.setFont(SmallFont);                  //Birazdan yazacağımız yazıların küçük fontla yazılmasını sağlıyoruz.
  myGLCD.print("Dakikadaki", CENTER, 0);
  myGLCD.print("Nabziniz:", CENTER, 15);      //Ekrana "Dakikadaki Nabzinıiz:" yazdırıyoruz.
  myGLCD.setFont(BigNumbers);                 //Birazdan yazacağımız yazıların büyük sayı fontuyla yazılmasını sağlıyoruz.
  myGLCD.printNumI(0, CENTER, 25);            //Dakikadaki nabzınız yazısının altına 0 yazıyoruz.
  if (pulseSensor.begin()) {
    Serial.println("Pulse sensörü objesini oluşturduk."); //Pulse sensörü başarıyla başlatılırsa bilgisayara mesaj gönderiyoruz.
  }
}

void loop() {
  if (pulseSensor.sawStartOfBeat()) {         //Eğer nabız algılarsak
    nabiz = pulseSensor.getBeatsPerMinute();  //Dakikadaki nabzı nabiz değişkenine kaydediyoruz.
    
    if(nabiz<120){                            //Eğer nabız değeri 120 den küçükse
    myGLCD.clrScr();                          //5110 ekranı temizliyoruz.
    myGLCD.setFont(SmallFont);                //Birazdan yazacağımız yazıların küçük fontla yazılmasını sağlıyoruz.
    myGLCD.print("Dakikadaki", CENTER, 0);
    myGLCD.print("Nabziniz:", CENTER, 15);    //Ekrana "Dakikadaki Nabzinıiz:" yazdırıyoruz.
    myGLCD.setFont(BigNumbers);               //Birazdan yazacağımız yazıların büyük sayı fontuyla yazılmasını sağlıyoruz.
    myGLCD.printNumI( nabiz, CENTER, 25);     //Dakikadaki nabzınız yazısının altına dakikadki nabız değerini yazıyoruz.
    }
   
    else{                                     //Eğer nabız değeri 120 den küçük değilse
    myGLCD.clrScr();                          //5110 ekranı temizliyoruz.
    myGLCD.setFont(SmallFont);                //Birazdan yazacağımız yazıların küçük fontla yazılmasını sağlıyoruz.
    myGLCD.print("Dakikadaki", CENTER, 0);
    myGLCD.print("Nabziniz:", CENTER, 15);    //Ekrana "Dakikadaki Nabzinıiz:" yazdırıyoruz.
    myGLCD.setFont(BigNumbers);               //Birazdan yazacağımız yazıların büyük sayı fontuyla yazılmasını sağlıyoruz.
    myGLCD.printNumI(0, CENTER, 25);          //Dakikadaki nabzınız yazısının altına 0 yazıyoruz.
    }
  }
  delay(25);                                  //25 milisaniye bekleme
}
