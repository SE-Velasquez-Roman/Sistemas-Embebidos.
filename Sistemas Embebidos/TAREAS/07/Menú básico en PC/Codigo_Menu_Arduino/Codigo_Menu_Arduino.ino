///Declaramos variables
int lamp=0;
int ledr=1;
int leda=0;
int ledv=0;
int pot;

void setup()
{
 pinMode(6,OUTPUT);//pin de salida
 pinMode(5,OUTPUT);//pin de salida
 pinMode(3,OUTPUT);//pin de salida

 Serial.begin(9600);
}

void loop() {
  //Lectura del Pot
  pot = (analogRead(A0)/4);
  Serial.write(pot);
  delay(100);
  //Leds
  if(Serial.available())
  {
    char val = Serial.read();
    if(val == 'r') 
    {
     ledr=ledr+255;
     if(ledr==255){
     analogWrite(6,ledr);
     }
     else
     {
      ledr=0;
      analogWrite(6,ledr);
     }
    } 
      
    
    if(val=='a') 
    {
     leda=leda+255;
     if(leda==255){
     analogWrite(5,leda);
     }
     else
     {
      leda=0;
      analogWrite(5,leda);
     }
     }
    
    
    if(val=='v')
    { 
      ledv=ledv+255;
     if(ledv==255){
     analogWrite(3,ledv);
     }
     else
     {
      ledv=0;
      analogWrite(3,ledv);
     }
    }

    if(val== 'l') 
    {
      lamp=lamp+24;
      analogWrite(6, lamp);
      analogWrite(5, lamp);
      analogWrite(3, lamp);
      
      if(lamp>240)
      {
      lamp=0;
      analogWrite(6, lamp);
      analogWrite(5, lamp);
      analogWrite(3, lamp);
      }
    }
}
}
   
   
  
  
