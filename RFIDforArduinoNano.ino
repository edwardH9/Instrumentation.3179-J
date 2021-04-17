#include <LiquidCrystal.h>
#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
LiquidCrystal lcd(7,6,5,4,3,2);

//RFID PINS for Nano
//3.3 goes to 3.3v on board
//RST goes to Dig Pin 9
//gnd goes to gnd on board
//MISO goes to DIG PIN 12
//MOSI goes to DIG PIN 11
//SCK goes to DIG PIN 13
//SDA goes to DIG PIN 9 


//LCD rs=pin7,e=pin6, Digital display pins 5-2 in descending order on nano board but ascending order on lcd display
//Buzzpin = 8

void setup() 
{
  lcd.begin(16,2);
  lcd.clear();
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.print("Device Armed");
  lcd.setCursor(0,1);
  lcd.print(">Awaiting Input<");

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  int j=0;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "B5 37 0B 2D") 
  {
    lcd.clear();
    Serial.println("Authorized access");
    tone(8,250,500);
    //Added Code
    lcd.print("Access Granted"); 
    lcd.setCursor(0,1);
    delay(750);
    lcd.print("Welcome, Edward");
    delay(1750);
    lcd.clear();
    lcd.print("Device Armed");
    lcd.setCursor(0,1);
    lcd.print("Awaiting Input:");
  }
 else   {
  lcd.clear();
    Serial.println(" Access denied");
    //Added code
    tone(8,200,300);
    lcd.print("Access Denied");
    //Added code squared
    int j=0;
    for (j==0;j<3;j++){
      lcd.setCursor(0,1);
      lcd.print("Attempt ");
      lcd.print(j);
      lcd.print("/3");
    }

    delay(2250);
    lcd.clear();
    lcd.print("Device Armed");
    lcd.setCursor(0,1);
    lcd.print("Awaiting Input:");
  }
//End of Added Code  
} 
