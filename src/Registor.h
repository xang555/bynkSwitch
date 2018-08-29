
#include <Arduino.h>
/************** Pins Active Relays ****************/
#define CH1 7
#define CH2 6
#define CH3 5
#define CH4 4

/************** Pins Switch INPUT ****************/
byte sw1_1 = 15;
byte sw1_2 = 14;
byte sw2_1 = 13;
byte sw2_2 = 12;
byte sw3_1 = 11;
byte sw3_2 = 10;
byte sw4_1 = 9;
byte sw4_2 = 8;


/************** Status Relays ****************/
byte Status_CH1 = 0;
byte Status_CH2 = 0;
byte Status_CH3 = 0;
byte Status_CH4 = 0;

/************** Status Switches on push ****************/
byte btnPinState_SW1_1 = 0;
byte btnPinState_SW1_2 = 0;
byte btnPinState_SW2_1 = 0;
byte btnPinState_SW2_2 = 0;
byte btnPinState_SW3_1 = 0;
byte btnPinState_SW3_2 = 0;
byte btnPinState_SW4_1 = 0;
byte btnPinState_SW4_2 = 0;

/************** last Status Switches ****************/
byte lastButtonState_SW1_1 = 0;
byte lastButtonState_SW1_2 = 0;
byte lastButtonState_SW2_1 = 0;
byte lastButtonState_SW2_2 = 0;
byte lastButtonState_SW3_1 = 0;
byte lastButtonState_SW3_2 = 0;
byte lastButtonState_SW4_1 = 0;
byte lastButtonState_SW4_2 = 0;

/************** Checking Status Switches ****************/
bool is_boot1 = true;
bool is_boot2 = true;
bool is_boot3 = true;
bool is_boot4 = true;

/************** Save EEPROM Status Relays ****************/
int addrRelay1 = 0;
int addrRelay2 = 1;
int addrRelay3 = 2;
int addrRelay4 = 3;

byte SaveRelay1;
byte SaveRelay2;
byte SaveRelay3;
byte SaveRelay4;





