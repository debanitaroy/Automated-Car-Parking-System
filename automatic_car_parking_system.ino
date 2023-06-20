#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;
int s1=0, s2=0, s3=0, s4=0;
int flag1=0, flag2=0;
int slot=4;
void setup() {
  Serial.begin(9600);
  pinMode (2,INPUT);
  pinMode (3,INPUT);
  pinMode (5,INPUT);
  pinMode (6,INPUT);
  pinMode (9,INPUT);
  pinMode (10,INPUT);
  pinMode (11,INPUT);
  pinMode (12,OUTPUT);
  pinMode (13,OUTPUT);
  pinMode (17,OUTPUT);
  pinMode (4,OUTPUT);
  pinMode (7,OUTPUT);
  pinMode (8,OUTPUT);
  myservo.attach(6);
  //myservo.write(90);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("CAR  PARKING");
  delay(2000);
  lcd.clear();
  Read_Sensor();
  int total = s1+s2+s3+s4;
  slot=slot-total;
  }
void loop() {
  Read_Sensor();
  lcd.setCursor(0,0);
  lcd.print ("Empty Slots: ");
  lcd.print (slot);
  lcd.setCursor(0,1);
  if (s1==0)
  {lcd.print("1st");}
  else
  {lcd.print("   ");}
  lcd.setCursor(4,1);
  if (s2==0)
  {lcd.print("2nd");}
  else
  {lcd.print("   ");}
  lcd.setCursor(8,1);
  if (s3==0)
  {lcd.print("3rd");}
  else
  {lcd.print("   ");}
  lcd.setCursor(12,1);
  if (s4==0)
  {lcd.print("4th");}
  else
  {lcd.print("   ");}
  
  if (slot == 0 && flag1 == 0 && flag2 == 0)
  {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
  }
  if (slot>0 && flag1 == 0 && flag2 == 0)
  {
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  }
  if (digitalRead(3) == 0 && flag1 == 0)
  {
    if (slot>0)
    {
      flag1=1;
      if (flag2 == 0)
      {
        myservo.write(180);
        delay (500);
        slot=slot-1;
      }
    }
    else
    {
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print ("Sorry,");
      lcd.setCursor(0,1);
      lcd.print ("Parking is full");
      delay (3000);
      lcd.clear();
    }
  }
  if (digitalRead(5) == 0 && flag2 == 0)
  {
    flag2 = 1;
    if (flag1 == 0)
    {
      myservo.write(180);
      delay (250);
      slot=slot+1;
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
    }
  }
  if (flag1 == 1 && flag2 == 1)
  {
    myservo.write(90);
    delay (500);
    if (digitalRead(5)==1)
    {
      flag1=0;
      flag2=0;
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
    }
  }
  delay(1);}
void Read_Sensor() {
  s1=0, s2=0, s3=0, s4=0;
  if (digitalRead(2)==0)
  {
    s1=1;
    digitalWrite (17,LOW);
  }
  else
  {
    s1=0;
    digitalWrite (17,HIGH);
  }
  if (digitalRead(9)==0)
  {
    s2=1;
    digitalWrite (4,LOW);
  }
  else
  {
    s2=0;
    digitalWrite (4,HIGH);
  }
  if (digitalRead(10)==0)
  {
    s3=1;
    digitalWrite (7,LOW);
  }
  else
  {
    s3=0;
    digitalWrite (7,HIGH);
  }
  if (digitalRead(11)==0)
  {
    s4=1;
    digitalWrite (8,LOW);
  }
  else
  {
    s4=0;
    digitalWrite (8,HIGH);
  }
  
}
