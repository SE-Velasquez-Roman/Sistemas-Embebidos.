/*
 Digital Voltmeter using 4-Digit 7-segment Display
 www.circuits4you.com
*/
#include <TimerOne.h>
//Definimos las conecciones conel 74HC595 
const int Data =7;
const int Clock =8;
const int Latch =6;

const int SEG0 =5;
const int SEG1 =4;
const int SEG2 =3;
const int SEG3 =2;

int cc =0;
char Value [4];
const char SegData []=
{0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
//=============================================================
//============================Setup============================
//=============================================================
void setup () {
 // Inicializamos los pines como salidas
Serial . begin (9600);
pinMode ( Data , OUTPUT );
pinMode ( Clock , OUTPUT );
pinMode ( Latch , OUTPUT );
pinMode ( SEG0 , OUTPUT );
pinMode ( SEG1 , OUTPUT );
pinMode ( SEG2 , OUTPUT );
pinMode ( SEG3 , OUTPUT );
 //Inicializamos el Display
 cc =0;
 Timer1 . initialize (10000); // establecer un temporizador de longitud 100000microsegundos (o 0,1 seg - o 10Hz> el led parpadeará 5 veces, 5 ciclos de encendido y apagado, por segundo)
 Timer1 . attachInterrupt ( timerIsr ); // adjuntar la rutina de servicio aquí.
}
//=============================================================
//==============================Loop===========================
//=============================================================
void loop () {
 char Volt [4];
 int Voltage = analogRead ( A0 );
 //Para obtener el punto decimal fijo lo multiplicamos por 100
Voltage = (500/1024.0) * Voltage ; //Escalado de 0 a 5 V, es decir, de 0 a 1023 a 0 a 10 (en 10 pasos)
 //Voltaje de visualización en segmentos
sprintf ( Volt ,"%04d", Voltage ); //Obtenemos matriz ASCII en Volt
Serial . println ( Volt );
Value [0]= Volt [0] & 0x0F; //comenzamos con 0x0F para eliminarl el upper nibble
Value [1]= Volt [1] & 0x0F; //Ej. número 2 en ASCII es 0x32 que queremossó 2
Value [2]= Volt [2] & 0x0F;
Value [3]= Volt [3] & 0x0F;
delay (200);
}
//=============================================================
//======================Generates Bargraph=====================
//=============================================================
void DisplayDigit (char d )
{
 int i ;
for( i =0; i <8; i ++) //Desplazar bit a bit datos en el registro de turnos
{
 if(( d & 0x80)==0x80)
 {
 digitalWrite ( Data , HIGH );
 }
 else
 {
 digitalWrite ( Data , LOW );
 }
 d = d <<1;
 //Give Clock pulse
 digitalWrite ( Clock , LOW );
 digitalWrite ( Clock , HIGH );
}
 //Latch the data
digitalWrite ( Latch , LOW );
digitalWrite ( Latch , HIGH );
}
//===================================================================
//============TIMER 1 OVERFLOW INTTERRUPT FORDISPALY=================
//===================================================================
void timerIsr ()
{
 cc ++;
 if( cc ==5) //Solo tenemos 4 digitos
 { cc =1;}
 Scanner ();
 TCNT0 =0xCC;
}
//===================================================================
//====================SCAN DISPLAY FUNCTION==========================
//===================================================================
void Scanner ()
{
 switch ( cc ) //Dependiendo cual digito es seleccionado da un salida
 {
 case 1:
 digitalWrite ( SEG3 , HIGH );
 DisplayDigit ( SegData [ Value [0]]);
 digitalWrite ( SEG0 , LOW );
 break;
 case 2:
 digitalWrite ( SEG0 , HIGH );
 DisplayDigit ( SegData [ Value [1]] | 0x80); //0x80 enciende el punto decimal
 digitalWrite ( SEG1 , LOW );
 break;
 case 3:
 digitalWrite ( SEG1 , HIGH );
 DisplayDigit ( SegData [ Value [2]]);
 digitalWrite ( SEG2 , LOW );
 break;
 case 4:
 digitalWrite ( SEG2 , HIGH );
 DisplayDigit ( SegData [ Value [3]]);
 digitalWrite ( SEG3 , LOW );
 break;
 }
}
//===================================================================
//Codigo Revisado por Luis Uriel Sánchez López 

