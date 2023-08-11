/*
#################################################################
 #  SENIOR PROJECT 2                                           #
 #  TOPIC : DESIGN A SYSTEM OF WATERING THE PLANTS BY MOBILE   #
 #                                                             #
 #       Advisor: Assoc. Prof. TRUONG NGOC SON                 #
 #       Student:                                              #
 #        LE THI KIEU GIANG   ID Student: 19119001             #
 #        NGUYEN HUNG THINH   ID Student: 19119056             #
#################################################################
*/
#define BLYNK_TEMPLATE_ID "TMPL_Gr0TOMH"
#define BLYNK_DEVICE_NAME "SENIOR 2"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define BLYNK_DEBUG
#define APP_DEBUG
#define USE_NODE_MCU_BOARD
#define DHTPIN 5
#define DHTTYPE DHT11
#include "BlynkEdgent.h"
#include "DHT.h"
DHT dht(DHTPIN, DHTTYPE);
unsigned long times=millis();
bool isPushOn = false;
int Pump_button;
BlynkTimer timer;
void setup()
{
  Serial.begin(115200);
  delay(100);
  BlynkEdgent.begin();
  Blynk.syncVirtual(V0);
  delay(100);
  dht.begin();
  pinMode(A0,INPUT);
  pinMode(D2,OUTPUT);
  pinMode(D5,INPUT);
  pinMode(D6,INPUT);
}
BLYNK_WRITE(V0) { 
 Pump_button = param.asInt();
 isPushOn = true;
}
void loop() {
  BlynkEdgent.run();
  int Rain_notification = digitalRead(D5);
  int Waterlevel_notification = digitalRead(D6);
  int analog = analogRead(A0);
  int phantramao = map(analog, 0, 1023, 0, 100);
  int phantram = 100 - phantramao; 
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Blynk.virtualWrite(V5,Rain_notification);
  Blynk.virtualWrite(V7,Waterlevel_notification);
  // Create LED notification in Blynk Application 
  if (Rain_notification == 0 and Waterlevel_notification == 1){
    Blynk.virtualWrite(V6, 1);
    Blynk.virtualWrite(V4, 0);
    }else if (Rain_notification == 1 and Waterlevel_notification == 0)
    {
      for(int i = 0; i<5; i++)
      {
        Blynk.virtualWrite(V6, 1);
        Blynk.virtualWrite(V4, 1);
        delay(5);
        Blynk.virtualWrite(V6, 0);
        Blynk.virtualWrite(V4, 0);
        delay(5);
      }
  }
  if (Rain_notification == 0 and Waterlevel_notification == 0){
    Blynk.virtualWrite(V4, 0);
    for(int i = 0; i<5; i++){
      Blynk.virtualWrite(V6, 1);
      delay(5);
      Blynk.virtualWrite(V6, 0);
      delay(5);
    }
  }else if (Rain_notification == 1 and Waterlevel_notification == 1)
  {
    Blynk.virtualWrite(V6, 1);
    for(int i = 0; i<5; i++){
      Blynk.virtualWrite(V4, 1);
      delay(5);
      Blynk.virtualWrite(V4, 0);
      delay(5);
    }
  }
  // Create Threshold for Pump by D2 Pin of ESP8266
  if (Pump_button == 0){
    if (phantram <= 50){
      digitalWrite(D2,HIGH);
      isPushOn = false;
    }
    else if ( phantram > 50){
      digitalWrite(D2,LOW);
    }   
  }
    if(isPushOn == true){
      digitalWrite(D2,Pump_button);
      isPushOn = false;
    }
    // Send the value from board into V1, V2, V3 of Blynk Application
    Blynk.virtualWrite(V1, t); 
    Blynk.virtualWrite(V2, h);
    Blynk.virtualWrite(V3, phantram);
    // Display data in the Window of Serial motor 
    Serial.print("Percentage: "+ String(phantram) + "%\t");
    Serial.print("Humidity: " + String(h) + "%\t");
    Serial.println("Temperature: " + String(t) + "*C");
}
