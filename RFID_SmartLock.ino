#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define btn 5
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
SoftwareSerial mySerial(6,7);//rx tx
void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  mySerial.begin(115200);
  pinMode(btn,INPUT_PULLUP);

}
void loop() 
{
  // Look for new cards
    
     if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      return;
    }
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      return;
    }
    //Show UID on serial monitor
    Serial.print("UID tag :");
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    { if(mfrc522.uid.uidByte[i] < 0x0A){
      Serial.print(" 00"); 
    }else if(mfrc522.uid.uidByte[i] < 0x64 ){
      Serial.print("  0");
    }else{
      Serial.print(" ");
    }
    Serial.print(mfrc522.uid.uidByte[i]);
    if(mfrc522.uid.uidByte[i] < 0x0A){
     content.concat(String("00"));
    }else if(mfrc522.uid.uidByte[i] < 0x64 ){
      content.concat(String("0"));
    }
       //Serial.print(mfrc522.uid.uidByte[i] < 0x64 ? " 00" : " ");
      
       //content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       content.concat(String(mfrc522.uid.uidByte[i]));
       
    }
      Serial.println();
      Serial.println(content);
      mySerial.println(content);
      Serial.println();
      delay(3000);
} 
