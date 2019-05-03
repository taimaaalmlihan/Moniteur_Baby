#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <SI7021.h>

#define LAPIN A0 // PIN with Light sensor analog output 
#define LPPIN 4 // PIN with Light power input

SI7021 sensor;
static float light;


// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = A3;

// Parameters you can play with :

int txPower = 14; // from 0 to 20, default is 14
int spreadingFactor = 12; // from 7 to 12, default is 12
long signalBandwidth = 125E3; // 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3,41.7E3,62.5E3,125E3,250E3,500e3, default is 125E3
int codingRateDenominator=5; // Numerator is 4, and denominator from 5 to 8, default is 5
int preambleLength=8; // from 2 to 20, default is 8
//


#define SS 10
#define RST 8
#define DI0 2
#define BAND 865E6  // Here you define the frequency carrier



void setup() {
  Serial.begin(115200);
  sensor.begin();
 pinMode(LPPIN, OUTPUT);
 // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);
 
  while (!Serial);

  Serial.println("LoRa Sender");
  Serial.print("SetFrequency : ");
  Serial.print(BAND);
  Serial.println("Hz");
  Serial.print("SetSpreadingFactor : SF");
  Serial.println(spreadingFactor);

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
// LoRa.setPolarity(1);
 //LoRa.setFSK(); 
 
}

void loop() {
  
  // send packet
    int temperature = sensor.getCelsiusHundredths();
  temperature = temperature / 100;
  LoRa.beginPacket();
  LoRa.print("Temp : ");
  LoRa.print(temperature);  
  LoRa.print(" °C ");
 
  LoRa.endPacket();
 
 
  Serial.print("La température : ");
  Serial.print(temperature);
  Serial.println(" °C ");
 

   delay(1000);

    // humidity is an integer representing percent
  int humidity = sensor.getHumidityPercent();
  LoRa.beginPacket();
  LoRa.print("Hum : ");
  LoRa.print(humidity);  
  LoRa.print(" % ");
 
  LoRa.endPacket();
 
  Serial.print("La humidity : ");
  Serial.print(humidity);
  Serial.println(" % ");

  
  delay(1500);
  
   // read the input pin:
   int sensorValue = analogRead(A3);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  
  LoRa.beginPacket();
  LoRa.print("Son : ");
  LoRa.print(voltage);  
  LoRa.print(" V ");
  
  LoRa.endPacket();


  Serial.print("la son : ");
  Serial.print(voltage);
  Serial.println(" V ");
  

  delay(2000); 
    
    // temperature is an integer in hundredths
      light = readLight();
  LoRa.beginPacket();
  LoRa.print("Lum : ");
  LoRa.print(light);  
  LoRa.print(" Lx");
 
  LoRa.endPacket();


  Serial.print("la lumier : ");
  Serial.print(light);
  Serial.println(" Lx ");
 
 

  delay(2500);
}

float readLight() {
  float result;
  // Light sensor Voltage
digitalWrite(LPPIN, HIGH); // Power the sensor
delay(10);
int sensorValue = analogRead(LAPIN);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 3.3V):
  float voltage = sensorValue * (3.3 / 1023.0); // Batvalue is 3.3V
result = voltage*2000; // multiply by 2000 to have Lx
digitalWrite(LPPIN, LOW); // switch off the sensor
  return result;
}
