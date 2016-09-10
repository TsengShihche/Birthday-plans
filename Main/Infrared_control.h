#include <IRremote.h>
#include "Temperature.h"
long Onpower = 0x00FFA25D;//power
long On0 = 0x00FF6897;  // 0
long On1 = 0x00FF30CF;  // 1
long On2 = 0x00FF18E7;  // 2
long On3 = 0x00FF7A85;  // 3
long On4 = 0x00FF10EF;  // 4
long On5 = 0x00FF38C7;  // 5
long On6 = 0x00FF5AA5;  // 6
long On7 = 0x00FF42BD;  // 7 
long On8 = 0x00FF4AB5;  // 8
long On9 = 0x00FF52AD;  // 9
extern int setNumber;
extern decode_results results;

void control(decode_results *results){  //紅外縣遙控器
  if ((results->value) == Onpower){        
    if(setNumber==1){
    //  lcd.backlight(); 
      Serial.println("Turn ON");
     // lcdPrint("Turn ON");
      setNumber=0;
    }else{
      Serial.println("Turn OFF");
     // lcdPrint("Turn OFF");
      delay(100);
     // lcd.noBacklight();
      setNumber=1;
      }
    }
  if ((results->value) == On0){
     // lcdPrint("Temperature");
       // start_Temperature();
        Serial.print("Current humdity = ");
       // Serial.print(dat[0], DEC);
        Serial.print('.');
       // Serial.print(dat[1],DEC);
        Serial.println('%');

        Serial.print("Current temperature = ");
      //  Serial.print(dat[2], DEC);
        Serial.print('.');
      //  Serial.print(dat[3],DEC);
        Serial.println('C');
    }  
  if ((results->value) == On1){
    Serial.println("1");
   // lcd.print("1");
    }
  if ((results->value) == On2){
    Serial.println("2");
   // lcd.print("2");
    }
  if ((results->value) == On3){
    Serial.println("3");
   // lcd.print("3");
    }
  if ((results->value) == On4){
    Serial.println("4");
   // lcd.print("4");
    }
  if ((results->value) == On5){
    Serial.println("5");
  //  lcd.print("5");
    }
  if ((results->value) == On6){
    Serial.println("6");
   // lcd.print("6");
    }
  if ((results->value) == On7){
    Serial.println("7");
    //lcd.print("7");
    }
  if ((results->value) == On8){
    Serial.println("8");
    //lcd.print("8");
    }
  if ((results->value) == On9){
    Serial.println("9");
    //lcd.print("9");
    }
}
