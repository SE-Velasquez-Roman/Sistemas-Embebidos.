#pragma once
#include <MD_Menu.h>

//#include <LiquidCrystal_I2C.h> // Libreria
const bool AUTO_START = true;


/*#include <LiquidCrystal.h>
#define  LCD_RS    8
#define  LCD_ENA   9
#define  LCD_D4    4
#define  LCD_D5    LCD_D4+1
#define  LCD_D6    LCD_D4+2
#define  LCD_D7    LCD_D4+3


*/

#define  LCD_ROWS  4
#define  LCD_COLS  20
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const LiquidCrystal_I2C lcd(0x27,LCD_COLS,LCD_ROWS); 



#define DISPLAY_LCD  1
#define INPUT_SWITCH    1  // Entrada de los botones



// LCD display definitions

///static LiquidCrystal lcd(LCD_RS, LCD_ENA, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
//LiquidCrystal_I2C lcd(0x27,20,4); // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2) 
//LiquidCrystal_I2C lcd(0x27,20,4); // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2) 


const uint16_t MENU_TIMEOUT = 5000; // in milliseconds
const uint8_t LED_ROJO = 13;

const uint8_t V1 = 14;
const uint8_t V2 = 15;
const uint8_t V3 = 16;
const uint8_t V4 = 17;
const uint8_t  Pot = A1;
const uint8_t  lm35 = A2;




void setupNav(void);

bool display(MD_Menu::userDisplayAction_t, char* = nullptr);
MD_Menu::userNavAction_t navigation(uint16_t &incDelta);

MD_Menu::value_t *ESTLED(MD_Menu::mnuId_t id, bool bGet);
MD_Menu::value_t *LEDROJO(MD_Menu::mnuId_t id, bool bGet);
MD_Menu::value_t *V1DOMOT(MD_Menu::mnuId_t id, bool bGet);
MD_Menu::value_t *POT(MD_Menu::mnuId_t id, bool bGet);
MD_Menu::value_t *LM35(MD_Menu::mnuId_t id, bool bGet);


