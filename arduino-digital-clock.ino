#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);//lcd ekran nesnesini oluşturur
#include <virtuabotixRTC.h>
virtuabotixRTC myRTC(6, 7, 8);
String aylar[] = {"", "Ocak", "Şubat", "Mart", "Nisan", "Mayis", "Haziran", "Temmuz", "Ağustos", "Eylül", "Ekim", "Kasım", "Aralık"};
#include <SD.h>     //sd kart için kütüphane
#include <SPI.h>    //ssd kart için kütüphane
File myFile;//sd kart için dosya tanımlıyor

int buttonPin = 3; // Butonun bağlı olduğu pinin numarasını bir değişkene atar
#define led 2
int sayac;
int alarm1saat =10;
int alarm1dakika = 34;
int alarm1saniye = 10;

int alarm2saat = 10;
int alarm2dakika = 32;
int alarm2saniye = 30;

int alarm3saat = 10;
int alarm3dakika = 35;
int alarm3saniye = 00;

int alarm4saat = 0;
int alarm4dakika = 29;
int alarm4saniye = 1;

int alarm5saat = 10;
int alarm5dakika = 10;
int alarm5saniye = 1;

int alarm6saat = 10;
int alarm6dakika = 1;
int alarm6saniye = 10;

void setup() {
  
  pinMode (led, OUTPUT);
  //-------------------------------lcd için saat tarih kodları------------------

  //myRTC.setDS1302Time(00, 4, 22, 0, 10, 5, 2021); //anlık tarih ve saat bilgisini ekliyoruz.Daha sonra silip yeniden yüklenecek buda tarih ve saat bilgisinin gerçek zamanlı olarak çalışmasını sağlayacak.
  lcd.init();        
  lcd.backlight();  //lcdnin arka ışığını açar

  //-------------------------------sd kart için kodlar---------------------------

  Serial.begin(9600);
  while (!Serial)
  {
    ;
  }


  Serial.println("SD Kart başlatılıyor...");

  pinMode(4, OUTPUT);

  if (!SD.begin())
  {
    Serial.println("Başlatma başarısız oldu.");
    return;
  }
  Serial.println("Başlatma yapıldı.");

  //YAZMA KODLARI
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile)
  {
    Serial.println("test.txt dosyasına yazılıyor...");
    myFile.println("Alarm 1: ");
    myFile.print(alarm1saat);
    myFile.print(":");
    myFile.print(alarm1dakika);
    myFile.print(":");
    myFile.print(alarm1saniye);
    myFile.println("\n");

    myFile.println("Alarm 2: ");
    myFile.print(alarm2saat);
    myFile.print(":");
    myFile.print(alarm2dakika);
    myFile.print(":");
    myFile.print(alarm2saniye);
    myFile.println("\n");

    myFile.println("Alarm 3: ");
    myFile.print(alarm3saat);
    myFile.print(":");
    myFile.print(alarm3dakika);
    myFile.print(":");
    myFile.print(alarm3saniye);
    myFile.println("\n");

    myFile.println("Alarm 4: ");
    myFile.print(alarm4saat);
    myFile.print(":");
    myFile.print(alarm4dakika);
    myFile.print(":");
    myFile.print(alarm4saniye);
    myFile.println("\n");

    myFile.println("Alarm 5: ");
    myFile.print(alarm5saat);
    myFile.print(":");
    myFile.print(alarm5dakika);
    myFile.print(":");
    myFile.print(alarm5saniye);
    myFile.println("\n");

    myFile.println("Alarm 6: ");
    myFile.print(alarm6saat);
    myFile.print(":");
    myFile.print(alarm6dakika);
    myFile.print(":");
    myFile.print(alarm6saniye);
    myFile.println("\n");
    myFile.close();
    Serial.println("Bitti.");
  }

  else
  {
    Serial.println("test.txt dosyası açılırken hata.");
  }

  //OKUMA KODLARI
  myFile = SD.open("test.txt");
  if (myFile)
  {
    Serial.println("test.txt:");
    while (myFile.available())
    {
      Serial.write(myFile.read());
    }
    myFile.close();
  }
  else
  {
    Serial.println("test.txt dosyası okunurken hata.");
  }

  pinMode(buttonPin, INPUT); // // Butonun bağlı olduğu pini GİRİŞ pini olarak atar


}


void loop() {
  // put your main code here, to run repeatedly:
  myRTC.updateTime();

  lcd.setCursor(0, 0);
  lcd.print(myRTC.dayofmonth);
  lcd.print(" ");
  lcd.print(aylar[myRTC.month]);
  lcd.print(" ");
  lcd.print(myRTC.year);


  lcd.setCursor(0, 1);
  lcd.print("Saat:  ");
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  lcd.print(":");
  lcd.print(myRTC.seconds);
  lcd.print(" ");
  delay(1000);


  while((alarm1saat == myRTC.hours && alarm1dakika == myRTC.minutes && alarm1saniye == myRTC.seconds) || (alarm2saat == myRTC.hours && alarm2dakika == myRTC.minutes && alarm2saniye == myRTC.seconds) || (alarm3saat == myRTC.hours && alarm3dakika == myRTC.minutes && alarm3saniye == myRTC.seconds) || (alarm4saat == myRTC.hours && alarm4dakika == myRTC.minutes && alarm4saniye == myRTC.seconds) || (alarm5saat == myRTC.hours && alarm5dakika == myRTC.minutes && alarm5saniye == myRTC.seconds) || (alarm6saat == myRTC.hours && alarm6dakika == myRTC.minutes && alarm6saniye == myRTC.seconds)  ) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ALARM");
     
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
      delay(500);
    if (digitalRead(buttonPin) == HIGH) // Pinden HIGH değeri okunduysa butona basılmıştır
      {  break;
        lcd.clear();
        
        delay(20000);
  
      }
      }

  
}
