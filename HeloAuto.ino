#include <dht.h>
#include <LiquidCrystal.h>

#define dht_dpin A0

String num;
int i, randnum,
//sensor=A0,
fan=52, 
temp;
const int rs = 8, en = 9, d4 = 10, d5 =11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
dht DHT;

void setup() {
  // put your setup code here, to run once:
for(i=2;i<8;i++) {
pinMode(i, OUTPUT);
}
pinMode(52, OUTPUT);
//pinMode(sensor, INPUT);
Serial1.begin(9600);
Serial.begin(9600);
lcd.begin(16, 2);
delay(1000);
}

void clrscr() {
  for(int i = 0; i < 16; ++i) {
   lcd.write(' ');
  }
}

void alloff() {
  //turns off all LEDs
  
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  DHT.read11(dht_dpin);
  Serial.println(DHT.temperature); 
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Humidity=");
  lcd.print(DHT.humidity);
  lcd.print("%");  

if(Serial1.available()>0) {
  num = Serial1.readString();
  Serial.println(num);

if(DHT.temperature>20) {
    digitalWrite(fan, HIGH);
}
else if(DHT.temperature<20) {
    digitalWrite(fan, LOW);
}
     
  if(num == "*paint the town red#" || num == "*paint the town read#") {
     digitalWrite(2, HIGH);
     lcd.setCursor(0, 1);
     clrscr();
     lcd.setCursor(0, 1);
     lcd.print("Red lights on");
  }
  else if(num == "*turn on green light#") {
     alloff();
     digitalWrite(3, HIGH);
     digitalWrite(6, HIGH);
     digitalWrite(7, HIGH);
     lcd.setCursor(0, 1);
     clrscr();
     lcd.setCursor(0, 1);
     lcd.print("Green lights on");
  }
  else if(num == "*turn on blue light#") {
     digitalWrite(4, HIGH);
     lcd.setCursor(0, 1);
     clrscr();
     lcd.setCursor(0, 1);
     lcd.print("Blue light on");
  }
  else if(num == "*All on#") {
     digitalWrite(2, HIGH);
     digitalWrite(5, HIGH);
     digitalWrite(6, HIGH);
     digitalWrite(7, HIGH);
     lcd.setCursor(0, 1);
     clrscr();
     lcd.setCursor(0, 1);
     lcd.print("All lights on");
  }
  else if(num == "*let's party#" || num == "*lets party#") {
     while(!Serial1.available()>0) {
        randnum = random(1,9);
        digitalWrite(randnum, HIGH);
        delay(100);
        alloff();
        lcd.setCursor(0, 1);
        clrscr();
        lcd.setCursor(0, 1);
        lcd.print("Party");
     }
  }
  else if(num == "*turn off the fan#") {
      digitalWrite(fan, LOW);
  }
  else if(num == "*turn off the lights#") {
      alloff();
      lcd.setCursor(0, 1);
      clrscr();
  }
}
}

