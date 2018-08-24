/************** define register part ****************/
#define IODIRA 0x00 // I/O DIRECTION REGISTER A
#define IODIRB 0x01 // I/O DIECTION REGISTER B
#define GPIOA 0x12  // Set/Reset GPIOA REGISTER
#define GPIOB 0x13  // Set/Reset GPIOA REGISTER
#define GPPUA 0x0C  // GPIO PULL-UP RESISTOR REGISTER
#define GPPUB 0x0D  // GPIO PULL-UP RESISTOR REGISTER

/************* define command part ********************/
#define Address_byte 0x20 // control byte not include R/W bit use just 7 bit
#define Output_mode 0x00
#define Intput_mode 0xFF

/************** Status Relays ****************/
int Status_CH1 = 0;
int Status_CH2 = 0;
int Status_CH3 = 0;
int Status_CH4 = 0;

/************** Status Switches on push ****************/
int btnPinState_SW1_1 = 0x00;
int btnPinState_SW1_2 = 0x00;
int btnPinState_SW2_1 = 0x00;
int btnPinState_SW2_2 = 0x00;
int btnPinState_SW3_1 = 0x00;
int btnPinState_SW3_2 = 0x00;
int btnPinState_SW4_1 = 0x00;
int btnPinState_SW4_2 = 0x00;

/************** last Status Switches ****************/
int lastButtonState_SW1_1 = 0x00;
int lastButtonState_SW1_2 = 0x00;
int lastButtonState_SW2_1 = 0x00;
int lastButtonState_SW2_2 = 0x00;
int lastButtonState_SW3_1 = 0x00;
int lastButtonState_SW3_2 = 0x00;
int lastButtonState_SW4_1 = 0x00;
int lastButtonState_SW4_2 = 0x00;

/************** Checking Status Switches ****************/
bool is_boot1 = true;
bool is_boot2 = true;
bool is_boot3 = true;
bool is_boot4 = true;

/************** Write OUTPUT to Relay ****************/
char out_PUT[] = {'0', '0', '0', '0', '0', '0', '0', '0'};
int sender = 0x00;

