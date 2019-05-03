#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`

#define interruptPin 0 // PIN 0 for interrupt with PRG button
bool Pushdetected = false; // reset peak freq
int buzzer = 23 ;
int lum_max=700;

void gotPush(){   // reset peak freq on interrupt
 Pushdetected = true;
}

// Parameters you can play with :

int txPower = 14; // from 0 to 20, default is 14
int spreadingFactor = 12; // from 7 to 12, default is 12
long signalBandwidth = 125E3; // 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3,41.7E3,62.5E3,125E3,250E3,500e3, default is 125E3
int codingRateDenominator=5; // Numerator is 4, and denominator from 5 to 8, default is 5
int preambleLength=8; // from 2 to 20, default is 8
String temp, hum, son, lum;
String text;

#define SS 18
#define RST 14
#define DI0 26
#define BAND 865E6  // Here you define the frequency carrier

SSD1306 display(0x3c, 4, 15); // Set the display

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Receiver");
  Serial.print("SetFrequency : ");
  Serial.print(BAND);
  Serial.println("Hz");
  Serial.print("SetSpreadingFactor : SF");
  Serial.println(spreadingFactor);

 // init screen
  pinMode(16,OUTPUT);
  digitalWrite(16, LOW); // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH);

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  

  SPI.begin();
  LoRa.setPins(SS,RST,DI0);

  

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
 LoRa.setTxPower(txPower,1);
 LoRa.setSpreadingFactor(spreadingFactor);
 LoRa.setSignalBandwidth(signalBandwidth);
 LoRa.setCodingRate4(codingRateDenominator);
 LoRa.setPreambleLength(preambleLength);

 display.drawString(5,5,"LoRa Receiver");
  display.display();
 


  // Define interrupt on PRG button to reset peak freq
  pinMode(interruptPin, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(interruptPin), gotPush, CHANGE);
  pinMode (buzzer, OUTPUT) ;

}
void loop() {
   // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    display.clear();
    display.display();
    // received a packet
    Serial.print("Received packet '");
    
      
     
    // read packet
    while (LoRa.available()) {
      
      text = (char)LoRa.read();
      Serial.print(text);      
      char currentid[64];
      text.toCharArray(currentid,64);
      display.drawString(10,5,currentid);
      //If lum plus de 700
      
    } 
  }
{
  unsigned char i, j ;
 while (1)
 
  {
char lum;
if(lum > lum_max ){(Pushdetected);
  delay (90000000000000000);
}
  for (i = 0; i <80; i++) // When a frequency sound
     
    {
       digitalWrite (buzzer, HIGH) ; //send tone
      delay (1) ;
      digitalWrite (buzzer, LOW) ; //no tone
      delay (1) ;
       }

   for (i = 0; i <100; i++) 
    {
      digitalWrite (buzzer, HIGH) ;
      delay (2) ;
      digitalWrite (buzzer, LOW) ;
      delay (2) ;
    }
     }
      }
   
  }
 
 
  
