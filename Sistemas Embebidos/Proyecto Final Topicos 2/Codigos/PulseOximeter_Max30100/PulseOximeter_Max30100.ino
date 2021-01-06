 //Viral Science www.youtube.com/c/viralscience  www.viralsciencecreativity.com
//Pulse Heart Rate BPM and Oxygen SpO2 Monitor

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "OakOLED.h"
 
#define REPORTING_PERIOD_MS 1000
OakOLED oled;
 
char auth[] = "aENE1Hr9BEmoQ0s5A0mfjNAzhC_N_P25";             // Authentication Token Sent by Blynk
char ssid[] = "cmcdb01";        //WiFi SSID
char pass[] = "ci4xlrt5aH";        //WiFi Password
 
// Connections : SCL PIN - D1 , SDA PIN - D2 , INT PIN - D0
PulseOximeter pox;
 
float BPM, SpO2, celsius;
uint32_t tsLastReport = 0;
 
const unsigned char bitmap [] PROGMEM=
{
0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x00, 0x0f, 0xe0, 0x7f, 0x00, 0x3f, 0xf9, 0xff, 0xc0,
0x7f, 0xf9, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xf0,
0xff, 0xf7, 0xff, 0xf0, 0xff, 0xe7, 0xff, 0xf0, 0xff, 0xe7, 0xff, 0xf0, 0x7f, 0xdb, 0xff, 0xe0,
0x7f, 0x9b, 0xff, 0xe0, 0x00, 0x3b, 0xc0, 0x00, 0x3f, 0xf9, 0x9f, 0xc0, 0x3f, 0xfd, 0xbf, 0xc0,
0x1f, 0xfd, 0xbf, 0x80, 0x0f, 0xfd, 0x7f, 0x00, 0x07, 0xfe, 0x7e, 0x00, 0x03, 0xfe, 0xfc, 0x00,
0x01, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x3f, 0xc0, 0x00,
0x00, 0x0f, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//========================================================================================================
//========================================================================================================
//========================================================================================================
#define PIN_UPTIME V6
BLYNK_READ(PIN_UPTIME)
{
  Blynk.virtualWrite(PIN_UPTIME, millis() / 1000);
}

BlynkTimer timer;

void myTimerEvent()
{
  int analogValue = analogRead(A0); //reading the sensor on A0
  float millivolts = (analogValue/1024.0) * 3300; //3300 is the voltage provided by NodeMCU
  celsius = millivolts/10;
  Blynk.virtualWrite(V5, celsius); //sending to Blynk
}
//========================================================================================================
//========================================================================================================
//========================================================================================================

 
void onBeatDetected()
{
    //Serial.println("Beat Detected!");
    oled.drawBitmap( 60, 20, bitmap, 28, 28, 1);
    oled.display();
}
 
void setup()
{
    Serial.begin(115200);
    oled.begin();
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(1);
    oled.setCursor(0, 0);
 
    oled.println("Inicilizando Oximetro");
    oled.display();
    
    pinMode(16, OUTPUT);
    Blynk.begin(auth, ssid, pass);
    timer.setInterval(1000L, myTimerEvent);
 
    //Serial.print("Initializing Pulse Oximeter..");
 
    if (!pox.begin())
    {
         //Serial.println("FAILED");
         oled.clearDisplay();
         oled.setTextSize(1);
         oled.setTextColor(1);
         oled.setCursor(0, 0);
         oled.println("PROCESO FALLIDO");
         oled.display();
         for(;;);
    }
    else
    {
         oled.clearDisplay();
         oled.setTextSize(1);
         oled.setTextColor(1);
         oled.setCursor(0, 0);
         oled.println("EXITO");
         oled.display();
         //Serial.println("SUCCESS");
         pox.setOnBeatDetectedCallback(onBeatDetected);
    }
 
    // The default current for the IR LED is 50mA and it could be changed by uncommenting the following line.
     //pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
}
 
void loop()
{
    pox.update();
    Blynk.run();
    timer.run();
 
    BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS)
    {
        
 
        Blynk.virtualWrite(V7, BPM);
        Blynk.virtualWrite(V8, SpO2);
        
        oled.clearDisplay();
        oled.setTextSize(1);
        oled.setTextColor(1);
        oled.setCursor(0,16);
        oled.println(pox.getHeartRate());
 
        oled.setTextSize(1);
        oled.setTextColor(1);
        oled.setCursor(0, 0);
        oled.println("Latidos BPM");
 
        oled.setTextSize(1);
        oled.setTextColor(1);
        oled.setCursor(0, 30);
        oled.println("Spo2");
 
        oled.setTextSize(1);
        oled.setTextColor(1);
        oled.setCursor(0,45);
        oled.println(pox.getSpO2());
        oled.display();

        Serial.print(BPM);
        Serial.print(",");
        Serial.print(SpO2);
        Serial.print(",");
        Serial.print(celsius);
        Serial.print(",");
        Serial.println();
 
        tsLastReport = millis();
    }
        
        
}
