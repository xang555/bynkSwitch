#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include "Registor.h"

/************** Status Relays ****************/
byte Status_CH1 = 0;
byte Status_CH2 = 0;
byte Status_CH3 = 0;
byte Status_CH4 = 0;

/************** Status Switches on push ****************/
byte btnPinState_SW1_1 = 0x00;
byte btnPinState_SW1_2 = 0x00;
byte btnPinState_SW2_1 = 0x00;
byte btnPinState_SW2_2 = 0x00;
byte btnPinState_SW3_1 = 0x00;
byte btnPinState_SW3_2 = 0x00;
byte btnPinState_SW4_1 = 0x00;
byte btnPinState_SW4_2 = 0x00;

/************** last Status Switches ****************/
int lastButtonState_SW1_1 = 0x00;
int lastButtonState_SW1_2 = 0x00;
int lastButtonState_SW2_1 = 0x00;
int lastButtonState_SW2_2 = 0x00;
int lastButtonState_SW3_1 = 0x00;
int lastButtonState_SW3_2 = 0x00;
int lastButtonState_SW4_1 = 0x00;
int lastButtonState_SW4_2 = 0x00;

byte buttonPushCounter1 = 0;
byte buttonPushCounter2 = 0;

bool is_boot1 = true;

char out_PUT[] = {'0', '0', '0', '0', '0', '0', '0', '0'};
int sender = 0x00;
String S;

char auth[] = "e45fa5940c20455b9d492a47af01aac4";

char ssid[] = "TOCK-95";
char pass[] = "02076993003";
SimpleTimer timer;

void setup()
{

  Serial.begin(115200); //Start serial for output
  Wire.begin();
  WriteOutput(Address_byte, IODIRA, Output_mode); // setup output port
  WriteOutput(Address_byte, IODIRB, Intput_mode); // setup input port
  WriteOutput(Address_byte, GPPUB, Intput_mode);  // setup output_mode port
  is_boot1 = true;

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {

    delay(100);
    Serial.print(".");
    checkPhysicalButton();
    is_boot1 = false;
  }
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10L, checkPhysicalButton);
}

BLYNK_CONNECTED()
{
  // Alternatively, you could override server state using:
  Blynk.virtualWrite(V3, Status_CH1);
  Blynk.syncVirtual(V3);
}

BLYNK_WRITE(V3)
{ // Map this Virtual Pin to your  Mobile Blynk apps widget.
  Status_CH1 = param.asInt();

  if (Status_CH1 == 1)
  {
    out_PUT[0] = '1';
  }
  else
  {
    out_PUT[0] = '0';
  }

  is_boot1 = false;
}

void loop()
{

  Blynk.run();
  timer.run();
}

void WriteOutput(byte ControlByte, byte RegisterAddress, byte Value)
{

  Wire.beginTransmission(ControlByte); //Send ID Code
  Wire.write(RegisterAddress);         //Send Data
  Wire.write(Value);
  Wire.endTransmission(); //Stop Condition
}

byte ReadInput(byte ControlByte, byte RegisterAddress)
{

  Wire.beginTransmission(ControlByte);
  Wire.write(RegisterAddress);
  Wire.endTransmission();
  Wire.requestFrom(ControlByte, 1);
  return (Wire.read());
}

void checkPhysicalButton()
{

  btnPinState_SW1_1 = ReadInput(Address_byte, GPIOB);
  btnPinState_SW1_2 = ReadInput(Address_byte, GPIOB);
  if (!is_boot1)
  {

    if (btnPinState_SW1_1 != lastButtonState_SW1_1)
    {
      if (btnPinState_SW1_1 == 0x7F)
      {

        Status_CH1 = !Status_CH1;
        Blynk.virtualWrite(V3, Status_CH1);
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }

    if (btnPinState_SW1_2 != lastButtonState_SW1_2)
    {
      if (btnPinState_SW1_2 == 0xBF)
      {

        Status_CH1 = !Status_CH1;
        Blynk.virtualWrite(V3, Status_CH1);
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
  }

  if (Status_CH1 == 1)
  {
    out_PUT[0] = '1';
  }
  else
  {
    out_PUT[0] = '0';
  }

  S = out_PUT;
  sender = S.toInt();

  WriteOutput(Address_byte, GPIOA, sender);

  lastButtonState_SW1_1 = btnPinState_SW1_1;
  lastButtonState_SW1_2 = btnPinState_SW1_2;
}
