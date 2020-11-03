import controlP5.*;
import processing.serial.*;

Serial port;

ControlP5 cp5;
PFont font;
void setup()
{
  size(200,300);//tamaño de la ventana (ancho,alto)
  
  printArray(Serial.list());
  
  port = new Serial(this,"COM3",9600);
  
  cp5= new ControlP5(this);
  font = createFont("Impact",20);
  
  cp5.addButton("red")
  .setPosition(60,60)// posición del boton led rojo
  .setSize(85,30)
  .setFont(font)
  ;
  cp5.addButton("blue")//posición del boton led Amarillo
  .setPosition(60,100)
  .setSize(85,30)
  .setFont(font)
  ;
  
  cp5.addButton("green")//posición del boton led Verde
  .setPosition(60,140)
  .setSize(85,30)
  .setFont(font)
  ; 
  
  cp5.addButton("Lampara")//posición del boton led Verde
  .setPosition(60,190)
  .setSize(85,30)
  .setFont(font)
  ; 
}
void draw()
{
  background(0,0,0);
  fill(255, 255, 255);
  textFont(font);
  text("Equipo 4",70,20);
  text("control de led",45,40);// posición del texto 2 
}

void red()
{
  port.write('r');
}
void blue()
{
  port.write('a');
}
void green()
{
  port.write('v');
}
void Lampara()
{
  port.write('l');
}
