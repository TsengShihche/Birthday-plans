#include <IRremote.h>
#include <LiquidCrystal_I2C.h>
extern LiquidCrystal_I2C lcd;
#include "Temperature.h"
long Onpower = 0x00FFA25D;//power
long change = 0x00FF9867;///change
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
extern int cursorNumber;


void control(decode_results *results){  //紅外縣遙控器
  if ((results->value) == Onpower){        
    if(setNumber==1){
      lcd.clear();
      lcd.backlight(); 
      Serial.println("Turn ON");
      lcdPrint("Turn ON");
      setNumber=0;
    }else{
      Serial.println("Turn OFF");
      lcdPrint("Turn OFF");
      delay(100);
      lcd.clear();
      lcd.noBacklight();
      setNumber=1;
      }
    }
  if ((results->value) == change){
    if(cursorNumber == 0){
      Serial.println("set Cursor at First");
      lcd.setCursor(0, 0);
      cursorNumber=1;
    }else if(cursorNumber == 1){
      Serial.println("set Cursor at Twice");
      lcd.setCursor(0, 1);
      cursorNumber=0;
    }
  }
  if ((results->value) == On0){
      lcdPrint("Temperature:");
      Temperature();
    }  
  if ((results->value) == On1){
    Serial.println("1");
    lcdPrint("abcdefghijklmnopqrstuvwxyz");
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
    for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }
    }
}
