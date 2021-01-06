#include <LiquidCrystal.h>
#include <TimerOne.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

int HBSensor = 4;
int HBCount = 0;
int HBCheck = 0;
int TimeinSec = 0;
int HBperMin = 0;
int HBStart = 2;
int HBStartCheck = 0;


float tempC; // Variable para almacenar el valor obtenido del sensor (0 a 1023)
int pinLM35 = 0; // Variable del pin de entrada del sensor (A0)


void setup() {
  // put your setup code here, to run once:
  lcd.begin(20, 4);
  pinMode(HBSensor, INPUT);
  pinMode(HBStart, INPUT_PULLUP);
  Timer1.initialize(800000); 
  Timer1.attachInterrupt( timerIsr );
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Actual HB: ");
  lcd.setCursor(0,1);
  lcd.print("Tiempo (S) : ");
  lcd.setCursor(0,2);
  lcd.print("HB por Min  : 0.0");
}

void loop() {
  if(digitalRead(HBStart) == LOW){lcd.setCursor(0,3);lcd.print("HB Contando.");HBStartCheck = 1;}
  if(HBStartCheck == 1)
  {
      if((digitalRead(HBSensor) == HIGH) && (HBCheck == 0))
      {
        HBCount = HBCount + 1;
        HBCheck = 1;
        lcd.setCursor(13,0);
        lcd.print(HBCount);
        lcd.print(" ");

////////////////////////////////

 tempC = analogRead(pinLM35); 
   
  // Calculamos la temperatura con la fórmula
  tempC = (5.0 * tempC * 100.0)/1024.0; 
 
  // Envia el dato al puerto serial
  //Serial.print(tempC);
  // Salto de línea
  //Serial.print("\n");

           lcd.setCursor(15,0);
          lcd.print(tempC);
  
////////////////////////////////7        
      }
      if((digitalRead(HBSensor) == LOW) && (HBCheck == 1))
      {
        HBCheck = 0;   
      }
      if(TimeinSec == 10)
      {
          HBperMin = HBCount * 6;
          HBStartCheck = 0;
          lcd.setCursor(14,2);
          lcd.print(HBperMin);
          lcd.print(" ");
          lcd.setCursor(0,3);
          lcd.print("Presione Boton...");
          HBCount = 0;
          TimeinSec = 0;      
      }



      /////////////////////////////
      /////lm35

 tempC = analogRead(pinLM35); 
   
  // Calculamos la temperatura con la fórmula
  tempC = (5.0 * tempC * 100.0)/1024.0; 
 
  // Envia el dato al puerto serial
  //Serial.print(tempC);
  // Salto de línea
  Serial.print("\n");
  
      
  }
}

void timerIsr()
{
  if(HBStartCheck == 1)
  {
      TimeinSec = TimeinSec + 1;
      lcd.setCursor(14,1);
      lcd.print(TimeinSec);
      lcd.print(" ");
  }
}
