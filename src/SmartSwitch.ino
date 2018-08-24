#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include "Registor.h"

byte ledState = 0;
byte btnPinState1 = 0x00;
byte btnPinState2 = 0x00;

int lastButtonState1 = 0x00;
int lastButtonState2 = 0x00;

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
  Blynk.virtualWrite(V3, ledState);
  Blynk.syncVirtual(V3);
}

BLYNK_WRITE(V3)
{ // Map this Virtual Pin to your  Mobile Blynk apps widget.
  ledState = param.asInt();

  if (ledState == 1)
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

  btnPinState1 = ReadInput(Address_byte, GPIOB);
  btnPinState2 = ReadInput(Address_byte, GPIOB);
  if (!is_boot1)
  {

    if (btnPinState1 != lastButtonState1)
    {
      if (btnPinState1 == 0x7F)
      {

        ledState = !ledState;
        Blynk.virtualWrite(V3, ledState);
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }

    if (btnPinState2 != lastButtonState2)
    {
      if (btnPinState2 == 0xBF)
      {

        ledState = !ledState;
        Blynk.virtualWrite(V3, ledState);
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
  }

  if (ledState == 1)
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

  lastButtonState1 = btnPinState1;
  lastButtonState2 = btnPinState2;
}

