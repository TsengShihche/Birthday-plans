#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Infrared_control.h"
#include <IRremote.h>

//*************************紅外線*************************
const int irReceiverPin = 11;             // 紅外線接收器 OUTPUT 訊號接在 pin 11
IRrecv irrecv(irReceiverPin);            // 定義 IRrecv 物件來接收紅外線訊號
decode_results results;                  // 解碼結果將放在 decode_results 結構的 result 變數裏
int setNumber =0;                       //開關變數
//*************************紅外線*************************
//***************************lcd************************** 
LiquidCrystal_I2C lcd(0x27,16,2);
//***************************lcd**************************
//***************************溫度*************************
int DHpin = 2;

//***************************溫度**************************
void setup(){ 
  Serial.begin(9600);
  pinMode(DHpin,OUTPUT);                 // 溫度感測
  irrecv.enableIRIn();                   // 啟動紅外線解碼
  lcd.init();                            //LCD初始化
  lcd.backlight();                       //LCD點燈
  lcd.setCursor(0, 0);                   // 設定游標位置在第一行行首
  lcdPrint("Hello, Myuser!");
  delay(1000);
  lcd.setCursor(0, 1);                   // 設定游標位置在第二行行首
  lcdPrint("TsengShihche");
  delay(1000);
  lcd.setCursor(0, 0);
  lcdPrint("You can Start!");
  delay(2000);
  lcd.noBacklight();
} 
void lcdPrint(String Char){          //LCD傳輸回圈
  for (int i=0;i<Char.length();i++)
    lcd.print(Char[i]);
}
void loop() { 
  if(Serial.available()){
    delay(100);
    lcd.clear();
    lcd.backlight();
    while (Serial.available() >0){
      lcd.write(Serial.read());
      }
    delay(5000);
    lcd.noBacklight();
    }

    
  if (irrecv.decode(&results)) {         // 解碼成功，收到一組紅外線訊號
    control(&results);                   // 遙控器控制判別
    irrecv.resume();                     // 繼續收下一組紅外線訊號        
  }
  delay(100);
}
