#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 16, 2);
 
 int s=0;
 int m=0;
 
volatile int st=0;

void setup() 
{
lcd.begin(16,2);
lcd.backlight ();

attachInterrupt(digitalPinToInterrupt(2),ISR_Min,FALLING);// Definimos los pines de interrupcion
attachInterrupt(digitalPinToInterrupt(3),ISR_S,FALLING);// We define the interrupt pins 
 pinMode(1,OUTPUT);
 lcd.setCursor(0,0);
 lcd.print("Bienbenido");
 delay(1000);
 
 lcd.clear();
 lcd.setCursor(0,0); 
 lcd.print("Restan: 00:00");
 
}

void loop() 
{

  while(st>0)
  {
    delay(800);
    st--;
    m = (st / 60) % 60;  //Convertimos los segundos totales en minutos
    s = st % 60;        //Convertimos los segundos totales en periodos de 60 segundos
    
    lcd.setCursor(0,0); lcd.print("Restan: ");
    
    //lcd.setCursor(0,1);
    
    if(m<10)lcd.print("0");
    
    lcd.print(m);
    lcd.print(":");
    
    if(s<10) lcd.print("0");
    lcd.print(s);
    if(st==0) {
    digitalWrite(1,HIGH);
    lcd.setCursor(0,1); lcd.print("Fin del conteo");
    }
    }
    delay(5000);
     lcd.clear();
     lcd.setCursor(0,0); 
     lcd.print("Restan: 00:00");
    digitalWrite(1,LOW);
    
}
void ISR_Min()
{
  st=st+60;
  delay(200);
}

void ISR_S()
{
  st=st+2;
  delay(200);
}
