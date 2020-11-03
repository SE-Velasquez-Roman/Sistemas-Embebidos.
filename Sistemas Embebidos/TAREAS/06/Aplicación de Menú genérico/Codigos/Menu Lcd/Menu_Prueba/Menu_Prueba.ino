#include "Menu_Prueba.h"
MD_Menu::value_t vBuf;
////////////7TITO
const PROGMEM MD_Menu::mnuHeader_t mnuHdr[] =
{
  {10, "Menu Principal",10, 13, 0},
  {11, "Integrantes",   30, 31, 0},
  {12, "S.Analogico",   40, 41, 0},
  {15, "VENTILADOR",    70, 73, 0},



  
  {13, "LEDS",          50, 51, 0},
  {14, "NOMBRES",       60, 62, 0},

  {16, "V1ON",          80, 83, 0},
  {17, "V1OFF",         84, 87, 0},
  
 
  
};

const PROGMEM MD_Menu::mnuItem_t mnuItm[] =
{ 
  {10, "Menu Led", MD_Menu::MNU_MENU, 13},
  {11, "Integrantes", MD_Menu::MNU_MENU, 14},
  {12, "Analogico", MD_Menu::MNU_MENU, 12},
  {13, "DOMOTICA", MD_Menu::MNU_MENU, 15},

 
  
  

  {60, "ROBERTO SAUL", MD_Menu::MNU_MENU, 14},
  {61, "ROMANSILLO", MD_Menu::MNU_MENU, 14},
  {62, "ING. TITO", MD_Menu::MNU_MENU, 14},

  
  
  {70, "ENCENDER V1", MD_Menu::MNU_MENU, 16},
  {73, "APAGAR V1", MD_Menu::MNU_MENU, 17},






  //////////////////////////////////
  {50, "Apagar Led", MD_Menu::MNU_INPUT, 10},
  {51, "Encender Led", MD_Menu::MNU_INPUT, 11},
  //////////////////////////////////////

  {40, "POTENCIOMETRO", MD_Menu::MNU_INPUT, 20},
  {41, "TEMPERATURA", MD_Menu::MNU_INPUT, 21},




  ///////////////////////////////
  {80, "ENCENDER V1", MD_Menu::MNU_INPUT, 12},
  {81, "ENCENDER V2", MD_Menu::MNU_INPUT, 13},
  {82, "ENCENDER V3", MD_Menu::MNU_INPUT, 14},
  {83, "ENCENDER V4", MD_Menu::MNU_INPUT, 15},
  {84, "APAGAR   V1", MD_Menu::MNU_INPUT, 16},
  {85, "APAGAR   V2", MD_Menu::MNU_INPUT, 17},
  {86, "APAGAR   V3", MD_Menu::MNU_INPUT, 18},
  {87, "APAGAR   V4", MD_Menu::MNU_INPUT, 19},
  
  
};

const PROGMEM MD_Menu::mnuInput_t mnuInp[] =
{
  { 10, "LEOFF",    MD_Menu::INP_RUN, ESTLED,   0,       0, 0,      0, 0,  0, nullptr},
  { 11, "LEON",     MD_Menu::INP_RUN, ESTLED,   0,       0, 0,      0, 0,  0, nullptr},

  { 12, "V1 ENC",    MD_Menu::INP_RUN, V1DOMOT,   0,       0, 0,      0, 0,  0, nullptr},
  { 13, "V1 ENC",    MD_Menu::INP_RUN, V1DOMOT,   0,       0, 0,      0, 0,  0, nullptr},
  { 14, "V1 ENC",    MD_Menu::INP_RUN, V1DOMOT,   0,       0, 0,      0, 0,  0, nullptr},
  { 15, "V1 ENC",    MD_Menu::INP_RUN, V1DOMOT,   0,       0, 0,      0, 0,  0, nullptr},

  { 16, "V1 OFF",    MD_Menu::INP_RUN, V1DOMOT,   0,       0, 0,      0, 0,  0, nullptr},
  { 17, "V1 OFF",    MD_Menu::INP_RUN, V1DOMOT,   0,       0, 0,      0, 0,  0, nullptr},
  { 18, "V1 OFF",    MD_Menu::INP_RUN, V1DOMOT,   0,       0, 0,      0, 0,  0, nullptr},
  { 19, "V1 OFF",    MD_Menu::INP_RUN, V1DOMOT,   0,       0, 0,      0, 0,  0, nullptr},

  { 20, "PPT",    MD_Menu::INP_INT, POT,   0,       0, 0,      0, 0,  0, nullptr},
  { 21, "PPT",    MD_Menu::INP_INT, LM35,   0,       0, 0,      0, 0,  0, nullptr},
 




  
};

MD_Menu M(navigation, display,        // Uso de navegacion y display
          mnuHdr, ARRAY_SIZE(mnuHdr), // datos del encabezado del menú
          mnuItm, ARRAY_SIZE(mnuItm), // datos del elemento del menú
          mnuInp, ARRAY_SIZE(mnuInp));// datos de entrada del menú

MD_Menu::value_t *ESTLED(MD_Menu::mnuId_t id, bool bGet)
{
  digitalWrite(LED_ROJO, id == 10 ? LOW : HIGH);
  return(nullptr);
}


MD_Menu::value_t *V1DOMOT(MD_Menu::mnuId_t id, bool bGet)

{
  //digitalWrite(V1, id == 12 ? LOW : HIGH);

  switch (id) {
  case 12:
    digitalWrite(V1, HIGH);
    break;
  case 13:
   digitalWrite(V2, HIGH);
    break;
  case 14:
   digitalWrite(V3, HIGH);
    break;

  case 15:
  digitalWrite(V4, HIGH);
  break;
  
  case 16:
    digitalWrite(V1, LOW);
    break;
  case 17:
   digitalWrite(V2, LOW);
    break;
  case 18:
   digitalWrite(V3, LOW);
    break;

  case 19:
  digitalWrite(V4, LOW);
  break;
 
    
 
}   



  return(nullptr);


  
  }

MD_Menu::value_t *POT(MD_Menu::mnuId_t id, bool bGet)


{
  
   int value=0;      //variable que almacena la lectura analógica raw
  int position;   //posicion del potenciometro en tanto por ciento
  int a=0;
  while (a<11)
  {
    // value = analogRead(Pot);          // realizar la lectura analógica raw
   int sensor = analogRead(A0);
    position = map(value, 0, 1023, 0, 100);  // convertir a porcentaje
    lcd.setCursor(0,2);
    lcd.print(sensor);
    lcd.setCursor(0,1);
    lcd.print("Resutlado:");
    //...hacer lo que se quiera, con el valor de posición medido
    delay(1000);
    a=a+1;
    lcd.setCursor(0,2);
    lcd.print("      ");
  }
  a=0;
  return(nullptr);
  
  
  }


  MD_Menu::value_t *LM35(MD_Menu::mnuId_t id, bool bGet)


  {
    
    
    
   int valor=0;      //variable que almacena la lectura analógica raw
  int position;   //posicion del potenciometro en tanto por ciento
  int a=0;
  float temp;
  while (a<11)
  {
   // value = analogRead(Pot);          // realizar la lectura analógica raw
   int temperatura = analogRead(A1);
    position = map(valor, 0, 1023, 0, 100);  // convertir a porcentaje
    temp = (temperatura * 5.0 * 100.0)/1023.0;
     lcd.setCursor(0,2);
     lcd.print("Temperatura:------------");
    
    lcd.setCursor(13,3);
    lcd.print(temp);
    //...hacer lo que se quiera, con el valor de posición medido
    delay(1000);
    a=a+1;
    lcd.setCursor(0,2);
    lcd.print("      ");
  }
  a=0;
  return(nullptr);  
    
    
    }
//int sensor = analogRead(A0);





 
void setup(void) {
  //Serial.begin(BAUD_RATE);
  //Serial.print("\n[Menu_Test Debug]");
  lcd.begin(LCD_COLS, LCD_ROWS);
  //lcd.clear();
  //lcd.home();
  
  pinMode(LED_ROJO, OUTPUT);
  pinMode (Pot,INPUT);
  pinMode (lm35,INPUT);
  pinMode(V1, OUTPUT);
  pinMode(V2, OUTPUT);
  pinMode(V3, OUTPUT);
  pinMode(V4, OUTPUT);

  display(MD_Menu::DISP_INIT);
  setupNav();

  M.begin();
  M.setMenuWrap(true);
  M.setAutoStart(AUTO_START);
  M.setTimeout(MENU_TIMEOUT);
}

void loop(void) {
  static bool prevMenuRun = true;

  // Detect if we need to initiate running normal user code
  if (prevMenuRun && !M.isInMenu())
    { 
  lcd.print("Selecciona Enter--->");
  lcd.setCursor(0, 1);
  lcd.print("<-----Equipo 4-----> ");
  lcd.setCursor(0, 2);
  lcd.print("<----Hola Mundo---->");
  lcd.setCursor(0, 3);
  lcd.print("<--Menu Basico SE-->");
 }
  //lcd.print("hola");
  prevMenuRun = M.isInMenu();

  // If we are not running and not autostart
  // check if there is a reason to start the menu
  if (!M.isInMenu() && !AUTO_START)
  {
    uint16_t dummy;

    if (navigation(dummy) == MD_Menu::NAV_SEL)
      M.runMenu(true);
  }
  M.runMenu();   // just run the menu code

  
 
  //Imprimimos por el monitor serie
  //lcd.print("El valor es = ");
 
 
}
