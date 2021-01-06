
import processing.serial.*;// libreria de comunicción serial

Serial myPort;// variable para el puerto de comunicación serial.


float BPM;
float PO2;
float Celcius;


PFont font;
PFont font1;

void setup()
{
  size(250,250);//tamaño de la ventana (ancho,alto)
  
  myPort = new Serial(this, Serial.list()[0],115200);// Nombre y velocidad del puesrto.
  println(Serial.list());// selecciona el puero utilizada
  myPort.bufferUntil('\n');

  
  font = createFont("Impact",20);
  font1= createFont("Impact",40);
  
}

void draw()
{
  
      colorMode(HSB,360,100,100);
      for(int i= -width; i< width*2; i++){
      float newHue = 195 - (i*0.45);
      stroke (newHue,70,80);
      line(i,0,i,height);}
  
  fill(0, 0, 0);
  
  titulo();// coloca el titulo.
  lectura();// muestra las variables.
  timer();// muestra fecha y hora.
   
}

//====================================================================================
//=============================== Creación de tpitulos ==============================
//====================================================================================

void titulo()
{
  textFont(font1);// tipo de letra
  text("Oximetro",50,40);// texto y posición.
}

//====================================================================================
//=================================== Lectura de datos ===============================
//====================================================================================
void lectura()
{
 int x1=50;//Modifican la posición de los textos de las variables.
 int y1= 80;
 int x2=160;
 int y2=80;
 int x3=60;
 int y3=120;
 
 String datos = myPort.readStringUntil('\n');// lee el puesrto hasta toparse con un Serial.println()
 
 if(datos != null)// verifica si el puerto tiene algo.
 {
  float[] sensores = float(split(datos, ','));// utiliza el caracter "," para separa los datos recibidos en diferenctes secciones de un vector
  BPM = sensores[0];
  PO2 = sensores[1];
  Celcius = sensores[2];
  
 }
 
 textFont(font);
 text("BPM:  " + BPM ,x1,y1);// imprime las variables leidas
 text("PO2:  " + PO2 ,x2,y2);
 text("Temperatura:  " + Celcius ,x3,y3);
}

//====================================================================================
//=================================== Fecha y hora ===================================
//====================================================================================
void timer()
{
 int s= second();
 int m= minute();
 int h = hour();
 int d = day();
 int M = month();
 int y= year();
 String t = nf(h,2)+ ":" + nf(m,2)+ ":" + nf(s,2);//muestra la hora.
 String c ="Fecha: " + d+ "/" + M + "/" + y;//muestra la fecha.
 text(t,90,160);
 text(c,50,180);
}
