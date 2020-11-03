//Importamos libreria ControlP5, llamamos la intancia 
import controlP5.*;//Biblioteca GUI por Andreas Schlegel para entorno Porcessing 
import processing.serial.*;//Importamos libreria de comunicación serial de arduino


Serial port;//the serial port:
ControlP5 cp5;//create ControlP5 object

//////////////////Variables///////////////////////////////
float mapval;
int val;
float r = 0;
float spe = 0.01;
float aguja;
int radio;

PFont font;
PFont font1;
PImage instru;
PImage pach;
PImage compassbody;
PImage comneedle;
//////////////////////////Void Setup/////////////////////
void setup()
{
  size(400,250);//tamaño de la ventana (ancho,alto)
  
  port = new Serial(this, Serial.list()[0], 9600);
  
  ///////////////cargamos nuestra imagen desde su ubicación/////////////
  instru=loadImage("instru.jpg");
  compassbody =loadImage("compassbody.png");
  comneedle =loadImage("comneedle.png");
  pach=loadImage("Piratas2.png");

  radio=min(width,height)/4;
  aguja=radio*0.05;
  
  //printArray(Serial.list());//prints all available serial ports
 // Open the port you are using at the rate you want:
  //port = new Serial(this, "COM5", 9600);
  
  
  cp5= new ControlP5(this);
  
  font = createFont("Impact",20);
  font1= createFont("Impact",40);
  
  botones();  //llamamos Void Botones
  
}
void draw()
{
  //background(0,0,0);//////////////////////
      colorMode(HSB,360,100,100);
      for(int i= -width; i< width*2; i++){
      float newHue = 195 - (i*0.5);
      stroke (newHue,70,80);
      line(i,0,i,height);}
////////////////////////////////////////////
  
  fill(0, 0, 0); //text color (r, g, b)
  titulo();      //llama a "void titulo"
  subtitulo();    //llama a "void subtitulo"
  brujula();   //llama a "void brujula"
  image(instru,170,135,100,160); //coloca nuestra imagen (x,y,px,px)
  cursor();
}
////////////////////////////////LED ROJO///////////////////////////////////
void red()
{
  port.write('r');
}
////////////////////////////////LED AZUL///////////////////////////////////
void blue()
{
  port.write('a');
}
////////////////////////////////LED VERDE///////////////////////////////////
void green()
{
  port.write('v');
}
////////////////////////////////LAMPARA///////////////////////////////////
void Lampara()
{
  port.write('l');
}
void brujula()
{
  int x=305;
  int y=130;
  if (port.available() > 0) 
   {
    val = port.read();//valor leido en el puerto, potenciometro
    mapval = map(val,0,255,0,6.25); //convertir el rango de una variable a otro
    //background(#A2F278);  
  } 
   pushMatrix();
   imageMode(CENTER);
   image(compassbody,x,y,160,160);
   translate(x,y);
   rotate(mapval);
   image(comneedle,0,0,50,90);
   println(val);
   popMatrix();
   float pot=map(val,0,255,0,360);
   
   text(pot,280,40);
   text("°",355,40);
}
void titulo()
{
  textFont(font1);
  text("Equipo 4",100,40);
}
void subtitulo()
{
  textFont(font);
  text("Control",20,20);// posición del texto 2
  text("de",40,40);  
  text("LED",35,60);
}
void botones()
{
  cp5.addButton("red")//Nombre del botón
  .setPosition(10,65)// posición del boton led rojo
  .setSize(85,30)//(width, height)
  .setFont(font)
  ;
  cp5.addButton("green")//Nombre del botón
  .setPosition(10,105)//posición del boton led Amarillo
  .setSize(85,30)//(width, height)
  .setFont(font)
  ;
  
  cp5.addButton("blue")//Nombre del botón
  .setPosition(10,145)//posición del boton 
  .setSize(85,30)//(width, height)
  .setFont(font)
  ; 
  
  cp5.addButton("Lampara")//Nombre del botón
  .setPosition(10,185)//posición del boton 
  .setSize(85,30)//(width, height)
  .setFont(font)
  ; 
}
void cursor()
{
  noCursor();
  image(pach,mouseX,mouseY,50,60);
}
