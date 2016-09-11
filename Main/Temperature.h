#include <LiquidCrystal_I2C.h>
extern LiquidCrystal_I2C lcd;
extern int DHpin;
void lcdPrint(String Char){          //LCD傳輸回圈
  for (int i=0;i<Char.length();i++){
    lcd.print(Char[i]);
  }
}
byte dat[5];
byte read_Data(void){
  byte data;
  for(int j=0; j<8; j++){
    if(digitalRead(DHpin) == LOW){
      while(digitalRead(DHpin) == LOW);
      delayMicroseconds(30);
      if(digitalRead(DHpin) == HIGH){
        data |= (1<<(7-j));
      }
      while(digitalRead(DHpin) == HIGH);
    }
  }
  return data;
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
  for(int i=0;i<4;i++) dat[i] = read_Data();
  pinMode(DHpin,OUTPUT);
  digitalWrite(DHpin,HIGH);
}
void Temperature(){
  start_Temperature();
  delay(500);
  start_Temperature();
  Serial.print("Current humdity = ");
  Serial.print(dat[0], DEC);
  Serial.print('.');
  Serial.print(dat[1],DEC);
  Serial.println('%');
  Serial.print("Current temperature = ");
  Serial.print(dat[2],DEC);
  Serial.print('.');
  Serial.print(dat[3],DEC);
  Serial.println('C');
  int T=(dat[2]);
  lcdPrint(String(T));
  lcd.print('.');
  lcd.print(dat[3], DEC);
  lcd.print('\'C');
  delay(700);
}
