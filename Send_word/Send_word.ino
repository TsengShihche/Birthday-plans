#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
//*************************紅外線*************************
long Onpower = 0x00FFA25D;//power
long On0 = 0x00FF6897;  //0
long On1 = 0x00FF30CF;  //1
long On2 = 0x00FF18E7;  //2
long On3 = 0x00FF7A85;  //3
long On4 = 0x00FF10EF;  //4
long On5 = 0x00FF38C7;  //5
long On6 = 0x00FF5AA5;  //6
long On7 = 0x00FF42BD;  //7 
long On8 = 0x00FF4AB5;  //8
long On9 = 0x00FF52AD;  //9
const int irReceiverPin = 11;             // 紅外線接收器 OUTPUT 訊號接在 pin 2
int setNumber =0;
IRrecv irrecv(irReceiverPin);            // 定義 IRrecv 物件來接收紅外線訊號
decode_results results;                  // 解碼結果將放在 decode_results 結構的 result 變數裏
//*************************紅外線*************************
//***************************lcd************************** 
LiquidCrystal_I2C lcd(0x27,16,2);
//***************************lcd**************************
//***************************溫度*************************
int DHpin = 2;
byte dat[5];
byte read_data()
{
  byte data;
  for(int i=0; i<8; i++)
  {
    if(digitalRead(DHpin) == LOW)
    {
      while(digitalRead(DHpin) == LOW);
      delayMicroseconds(30);
      if(digitalRead(DHpin) == HIGH) data |= (1<<(7-i));
      while(digitalRead(DHpin) == HIGH);
    }
  }
  return data;
}
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
      void control(decode_results *results){  //紅外縣遙控器
        lcd.clear();
        if ((results->value) == Onpower){        
          if(setNumber==1){
            lcd.backlight(); 
            Serial.println("Turn ON");
            lcdPrint("Turn ON");
            setNumber=0;
          }else{
            Serial.println("Turn OFF");
            lcdPrint("Turn OFF");
            delay(100);
            lcd.noBacklight();
            setNumber=1;
            }
          }
        if ((results->value) == On0){
            lcdPrint("Temperature");
            start_Temperature();
            Serial.print("Current humdity = ");
            Serial.print(dat[0], DEC);
            Serial.print('.');
            Serial.print(dat[1],DEC);
            Serial.println('%');
          
            
            Serial.print("Current temperature = ");
            Serial.print(dat[2], DEC);
            Serial.print('.');
            Serial.print(dat[3],DEC);
            Serial.println('C');
          }  
        if ((results->value) == On1){
          Serial.println("1");
          lcd.print("1");
          }
        if ((results->value) == On2){
          Serial.println("2");
          lcd.print("2");
          }
        if ((results->value) == On3){
          Serial.println("3");
          lcd.print("3");
          }
        if ((results->value) == On4){
          Serial.println("4");
          lcd.print("4");
          }
        if ((results->value) == On5){
          Serial.println("5");
          lcd.print("5");
          }
        if ((results->value) == On6){
          Serial.println("6");
          lcd.print("6");
          }
        if ((results->value) == On7){
          Serial.println("7");
          lcd.print("7");
          }
        if ((results->value) == On8){
          Serial.println("8");
          lcd.print("8");
          }
        if ((results->value) == On9){
          Serial.println("9");
          lcd.print("9");
          }
      }
          void start_Temperature()
          {
            digitalWrite(DHpin,LOW);
            delay(30);
            digitalWrite(DHpin,HIGH);
            delayMicroseconds(40);
            pinMode(DHpin,INPUT);
            while(digitalRead(DHpin) == HIGH);
            delayMicroseconds(80);
            if(digitalRead(DHpin) == LOW);
            delayMicroseconds(80);
            for(int i=0;i<4;i++) dat[i] = read_data();
            pinMode(DHpin,OUTPUT);
            digitalWrite(DHpin,HIGH);
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
