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

