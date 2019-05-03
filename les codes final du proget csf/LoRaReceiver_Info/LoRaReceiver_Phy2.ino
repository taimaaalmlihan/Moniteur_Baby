#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`



// Parameters you can play with :

int txPower = 14; // from 0 to 20, default is 14
int spreadingFactor = 12; // from 7 to 12, default is 12
long signalBandwidth = 125E3; // 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3,41.7E3,62.5E3,125E3,250E3,500e3, default is 125E3
int codingRateDenominator=5; // Numerator is 4, and denominator from 5 to 8, default is 5
int preambleLength=8; // from 2 to 20, default is 8

char text;
String temp, hum, son, lum;

#define SS 18
#define RST 14
#define DI0 26
#define BAND 865E6  // Here you define the frequency carrier

SSD1306 display(0x3c, 4, 15); // Set the display

int i = 0;

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
 
}

void loop() {
   // try to parse packet
  int packetSize = LoRa.parsePacket();
  char currentid[19];
  for (int j=0;j<19;j++){    
    currentid[j]=' ';
    }

display.clear();

display.drawString(2,5,temp);
display.drawString(2,25,hum);
display.drawString(2,45,lum);
display.display();
    
  if (packetSize) {
    i=0;
    
    
    // received a packet
    Serial.print("Received packet '");
    
      
     // read packet
     while (LoRa.available()) {
      
      text = (char)LoRa.read();
      Serial.print(text);      
      currentid[i]=text;

     i++;
      
    }
     if ( currentid[0] == 'T'){
      temp= currentid;
      }
      else if (currentid[0] == 'H'){
        hum= currentid;
        }
      else {
        lum= currentid;
        
        } 
     
 
    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());

   
  }
}




 
