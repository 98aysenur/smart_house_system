#include <LiquidCrystal.h>


#include<Keypad.h>
#include <Wire.h>
#define pir 20
const int yanginPin=A8;
const int buzzer=18;
int yangin = LOW; 
int c;
int a;
const int rs=12,en=13,d4=14,d5=15,d6=16,d7=17;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
const int sensor=A0;
float temp;
char keys[4][3]={
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}};
 
byte rowPin[4]={6,7,8,9};
byte colPin[3]={3,4,5};

String sifre = "2323"; 
int yer = 0;
int hata = 0;
int lamp = 21;
int redPin = 10;
int greenPin = 11;
Keypad keypad=Keypad(makeKeymap(keys),rowPin,colPin,4,3);
int toplam = 0;
float b=0.1039;


void setup()
{
   pinMode(yanginPin, INPUT);
 pinMode(buzzer, OUTPUT);
   pinMode(redPin,OUTPUT);
 pinMode(greenPin,OUTPUT);
 pinMode(lamp,OUTPUT);
  pinMode(19, INPUT);
Serial.begin(9600);
Serial.println("Hello");
delay(100);
analogReference(INTERNAL1V1);
lcd.begin(16,2);

 
}
 void loop()
{ 
  int temp=0;
  temp=analogRead(A0);
  temp=(temp*b)+1;
  //Serial.print(temp,1);
  lcd.setCursor(10,1);
  lcd.println(temp);
     a=digitalRead(19);        
   yangin = digitalRead(yanginPin);
  char sayi=keypad.getKey();
  String key[3];
  if(sayi)
 {
   Serial.println(sayi);
 //delay(500);
 
    if(sayi == '*' || sayi == '#')
      {
          yer = 0;
          kilitdurum(true);
          }
else if(sayi == sifre[yer])
  {
          
          yer++;
      }
  else if (sayi != sifre[yer] )
      {
          hata++;
          yer ++;
      }
if(yer == 4){
       if( hata >0)
        {
                
                hata = 0;
                yer = 0;
               kilitdurum(true);
            }
else if(yer == 4 && hata == 0)
            {
                yer = 0;
                hata = 0;
               kilitdurum(false);
              
            }
            }
            }
 
  if(a==HIGH){
    digitalWrite(lamp,HIGH);
    }
    else{
        digitalWrite(lamp,LOW);
       }


  if(yangin==HIGH)
{ 
  tone(buzzer,1000);
  digitalWrite(buzzer, HIGH);
  //delay(200);
  }
else 
{
   noTone(buzzer); 
 digitalWrite(buzzer, LOW); 
}


           if(temp>29){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.println("Sicaklik yukseK!!!");
           
            }  
            else if(temp<20){
              lcd.clear();
               lcd.setCursor(0,0);
               lcd.println("Sicaklik dustu!!!");
           
              }
              else if(19<temp<29){
               lcd.setCursor(0,0);
               lcd.print("                 ");
               
                }
     
            }

void kilitdurum(int kilit)
  {
    if (kilit)
      {
          digitalWrite(redPin, HIGH);
          digitalWrite(greenPin, LOW);
          delay(100);
      }
    else
      {
         
          digitalWrite(redPin, LOW);
          digitalWrite(greenPin, HIGH);
          delay(100);
          
      }
      }
