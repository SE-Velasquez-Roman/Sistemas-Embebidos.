
// Este codigo está pensado para trabajarce en plataformas arduino Mega.
// Utilice tres LEDs, cada uno asociado con distintas fuentes de 
// interrupción, en donde cada uno de ellos se enciende en 
// consecuencia de que se pulse una señal eléctrica que cambia 
// de “1” a “0” en alguna terminal de algún puerto 
// (cada entrada estará asociada con un LED en particular). 
 
/*=======================================================================================*/
/*========================================= SETUP =======================================*/
/*=======================================================================================*/
int i=0;
void setup() 
{
  pinMode(9, OUTPUT);// Definimos los pines de E/S
  pinMode(10, OUTPUT);//We define the I/O pins
  pinMode(11, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(2),ISR_R,FALLING);// Definimos los pines de interrupcion
  attachInterrupt(digitalPinToInterrupt(3),ISR_Y,FALLING);// We define the interrupt pins
  attachInterrupt(digitalPinToInterrupt(18),ISR_G,FALLING);

 
}
/*========================================================================================*/
/*======================================== LOOOP =========================================*/
/*========================================================================================*/
//Definimos la acción de ensendido a partir del valor presente en la varaiable
//"i", el motivo por el cual no utilizamos la funcioón case es que no funcionaba.

//We define the act of becoming understood from the value present in the varaiable
//"i", the reason we didn't use the case function is that it didn't work.

void loop() 
{
  if (i==0)//Todos apagados
  {
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
  }
  else if(i == 1)//Led rojo enecedido
  {
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
  }
  if (i==2)//Led amarillo enecedido
  {
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
  }
  if (i==3)//Led verde enecedido
  {
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
  }
  
}

void ISR_R()
{
  i=1;
}
void ISR_Y()
{
  i=2;
}
void ISR_G()
{
  i=3;
}
