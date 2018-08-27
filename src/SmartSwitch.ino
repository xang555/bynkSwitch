#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Registor.h"

char auth[] = "e45fa5940c20455b9d492a47af01aac4";
char ssid[] = "TOCK-95";
char pass[] = "02076993003";

SimpleTimer timer;
Adafruit_MCP23017 mcp;

void setup()
{

  Serial.begin(115200); //Start serial for output
  mcp.begin();          // use default address 0

  config_Pin();
  is_boot1 = true;
  is_boot2 = true;

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {

    delay(100);
    Serial.print(".");
    checkPhysicalButton();

  }
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10L, checkPhysicalButton);
}

BLYNK_CONNECTED()
{
  // Alternatively, you could override server state using:
  Blynk.virtualWrite(V3, Status_CH1);
  Blynk.virtualWrite(V4, Status_CH2);
  Blynk.syncVirtual(V3);
  Blynk.syncVirtual(V4);
}

BLYNK_WRITE(V3)
{ // Map this Virtual Pin to your  Mobile Blynk apps widget.
  Status_CH1 = param.asInt();

  if (Status_CH1 == 1)
  {
    mcp.digitalWrite(CH1, HIGH);
  }
  else
  {
    mcp.digitalWrite(CH1, LOW);
  }

  
}

BLYNK_WRITE(V4)
{ // Map this Virtual Pin to your  Mobile Blynk apps widget.
  Status_CH2 = param.asInt();

  if (Status_CH2 == 1)
  {
    mcp.digitalWrite(CH2, HIGH);
  }
  else
  {
    mcp.digitalWrite(CH2, LOW);
  }

  
}

void loop()
{

  Blynk.run();
  timer.run();
}

void checkPhysicalButton()
{

  btnPinState_SW1_1 = mcp.digitalRead(sw1_1);
  btnPinState_SW1_2 = mcp.digitalRead(sw1_2);
  btnPinState_SW2_1 = mcp.digitalRead(sw2_1);
  btnPinState_SW2_2 = mcp.digitalRead(sw2_2);


  if (!is_boot1)
  {

    if (btnPinState_SW1_1 != lastButtonState_SW1_1)
    {
      if (btnPinState_SW1_1 == LOW)
      {

        Status_CH1 = !Status_CH1;
        Blynk.virtualWrite(V3, Status_CH1);

        if (Status_CH1 == 1)
        {
          mcp.digitalWrite(CH1, HIGH);
        }
        else
        {
          mcp.digitalWrite(CH1, LOW);
        }
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }

    if (btnPinState_SW1_2 != lastButtonState_SW1_2)
    {
      if (btnPinState_SW1_2 == LOW)
      {

        Status_CH1 = !Status_CH1;
        Blynk.virtualWrite(V3, Status_CH1);

        if (Status_CH1 == 1)
        {
          mcp.digitalWrite(CH1, HIGH);
        }
        else
        {
          mcp.digitalWrite(CH1, LOW);
        }
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
  }

  if (!is_boot2)
  {

    if (btnPinState_SW2_1 != lastButtonState_SW2_1)
    {
      if (btnPinState_SW2_1 == LOW)
      {

        Status_CH2 = !Status_CH2;
        Blynk.virtualWrite(V4, Status_CH2);
        if (Status_CH2 == 1)
        {
          mcp.digitalWrite(CH2, HIGH);
        }
        else
        {
          mcp.digitalWrite(CH2, LOW);
        }

      } else 
      {

      }
      // Delay a little bit to avoid bouncing
      delay(50);

    }

    if (btnPinState_SW2_2 != lastButtonState_SW2_2)
    {
      if (btnPinState_SW2_2 == LOW)
      {

        Status_CH2 = !Status_CH2;
        Blynk.virtualWrite(V4, Status_CH2);
        if (Status_CH2 == 1)
        {
          mcp.digitalWrite(CH2, HIGH);
        }
        else
        {
          mcp.digitalWrite(CH2, LOW);
        }

      } else 
      {

      }
      // Delay a little bit to avoid bouncing
      delay(50);

    }

  }

  lastButtonState_SW1_1 = btnPinState_SW1_1;
  lastButtonState_SW1_2 = btnPinState_SW1_2;
  lastButtonState_SW2_1 = btnPinState_SW2_1;
  lastButtonState_SW2_2 = btnPinState_SW2_2;

  is_boot1 = false;
  is_boot2 = false;
}

void config_Pin()
{

  mcp.pinMode(CH1, OUTPUT);
  mcp.pinMode(CH2, OUTPUT);
  mcp.pinMode(CH3, OUTPUT);
  mcp.pinMode(CH4, OUTPUT);

  mcp.pinMode(sw1_1, INPUT);
  mcp.pinMode(sw1_2, INPUT);
  mcp.pinMode(sw2_1, INPUT);
  mcp.pinMode(sw2_2, INPUT);
  mcp.pinMode(sw3_1, INPUT);
  mcp.pinMode(sw3_2, INPUT);
  mcp.pinMode(sw4_1, INPUT);
  mcp.pinMode(sw4_2, INPUT);

  mcp.pullUp(sw1_1, HIGH);
  mcp.pullUp(sw1_2, HIGH);
  mcp.pullUp(sw2_1, HIGH);
  mcp.pullUp(sw2_2, HIGH);
  mcp.pullUp(sw3_1, HIGH);
  mcp.pullUp(sw3_2, HIGH);
  mcp.pullUp(sw4_1, HIGH);
  mcp.pullUp(sw4_2, HIGH);
}