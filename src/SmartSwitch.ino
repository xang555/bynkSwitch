// #define BLYNK_PRINT Serial

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <EEPROM.h>
#include "Adafruit_MCP23017.h"
#include "Registor.h"

char auth[] = "e45fa5940c20455b9d492a47af01aac4";
char ssid[] = "Tock";
char pass[] = "12345678";

SimpleTimer timer;
Adafruit_MCP23017 mcp;

WiFiClient wifiClient;

// This function tries to connect to the cloud using TCP
bool connectBlynk()
{
  wifiClient.stop();
  return wifiClient.connect(BLYNK_DEFAULT_DOMAIN, BLYNK_DEFAULT_PORT);
}

// This function tries to connect to your WiFi network
void connectWiFi()
{
  Serial.print("Connecting to ");
  Serial.println(ssid);

  if (pass && strlen(pass))
  {
    WiFi.begin((char *)ssid, (char *)pass);
  }
  else
  {
    WiFi.begin((char *)ssid);
  }

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
    checkPhysicalButton();
  }
}

void setup()
{

  Serial.begin(115200); //Start serial for output
  EEPROM.begin(512);
  mcp.begin(1); // use default address 0
  delay(100);
  Serial.println();
  read_EEPROM();
  delay(100);
  Serial.println();
  Serial.println();
  Serial.println();
  config_Pin();

  Status_CH1 = SaveRelay1 == 1 ? 1 : 0;
  Status_CH2 = SaveRelay2 == 1 ? 1 : 0;
  Status_CH3 = SaveRelay3 == 1 ? 1 : 0;
  Status_CH4 = SaveRelay4 == 1 ? 1 : 0;

  mcp.digitalWrite(CH1, Status_CH1);
  mcp.digitalWrite(CH2, Status_CH2);
  mcp.digitalWrite(CH3, Status_CH3);
  mcp.digitalWrite(CH4, Status_CH4);

  connectWiFi();
  connectBlynk();
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(50L, checkPhysicalButton);
}

BLYNK_CONNECTED()
{
  // Alternatively, you could override server state using:
  Blynk.virtualWrite(V3, Status_CH1);
  Blynk.virtualWrite(V4, Status_CH2);
  Blynk.virtualWrite(V5, Status_CH3);
  Blynk.virtualWrite(V6, Status_CH4);
  Blynk.syncVirtual(V3);
  Blynk.syncVirtual(V4);
  Blynk.syncVirtual(V5);
  Blynk.syncVirtual(V6);

}

BLYNK_WRITE(V3)
{ // Map this Virtual Pin to your  Mobile Blynk apps widget.
  Status_CH1 = param.asInt();

  if (Status_CH1 == 1)
  {
    mcp.digitalWrite(CH1, Status_CH1);
    Serial.println("CH1 = " + String(Status_CH1));
    EEPROM.write(addrRelay1, 1);
  }
  else
  {
    mcp.digitalWrite(CH1, Status_CH1);
    Serial.println("CH1 = " + String(Status_CH1));
    EEPROM.write(addrRelay1, 0);
  }
  EEPROM.commit();
}

BLYNK_WRITE(V4)
{ // Map this Virtual Pin to your  Mobile Blynk apps widget.
  Status_CH2 = param.asInt();

  if (Status_CH2 == 1)
  {
    mcp.digitalWrite(CH2, Status_CH2);
    Serial.println("CH2 = " + String(Status_CH2));
    EEPROM.write(addrRelay2, 1);
  }
  else
  {
    mcp.digitalWrite(CH2, Status_CH2);
    Serial.println("CH2 = " + String(Status_CH2));
    EEPROM.write(addrRelay2, 0);
  }
  EEPROM.commit();
}

BLYNK_WRITE(V5)
{ // Map this Virtual Pin to your  Mobile Blynk apps widget.
  Status_CH3 = param.asInt();

  if (Status_CH3 == 1)
  {
    mcp.digitalWrite(CH3, Status_CH3);
    Serial.println("CH3 = " + String(Status_CH3));
    EEPROM.write(addrRelay3, 1);
  }
  else
  {
    mcp.digitalWrite(CH3, Status_CH3);
    Serial.println("CH3 = " + String(Status_CH3));
    EEPROM.write(addrRelay3, 0);
  }
  EEPROM.commit();
}

BLYNK_WRITE(V6)
{ // Map this Virtual Pin to your  Mobile Blynk apps widget.
  Status_CH4 = param.asInt();

  if (Status_CH4 == 1)
  {
    mcp.digitalWrite(CH4, Status_CH4);
    Serial.println("CH4 = " + String(Status_CH4));
    EEPROM.write(addrRelay4, 1);
  }
  else
  {
    mcp.digitalWrite(CH4, Status_CH4);
    Serial.println("CH4 = " + String(Status_CH4));
    EEPROM.write(addrRelay4, 0);
  }
  EEPROM.commit();
}

void loop()
{

  // Reconnect WiFi
  if (WiFi.status() != WL_CONNECTED)
  {
    connectWiFi();
    return;
  }

  // Reconnect to Blynk Cloud
  if (!wifiClient.connected())
  {
    connectBlynk();
    return;
  }

  Blynk.run();
  timer.run();
}

void checkPhysicalButton()
{

  btnPinState_SW1_1 = mcp.digitalRead(sw1_1);
  btnPinState_SW1_2 = mcp.digitalRead(sw1_2);
  btnPinState_SW2_1 = mcp.digitalRead(sw2_1);
  btnPinState_SW2_2 = mcp.digitalRead(sw2_2);
  btnPinState_SW3_1 = mcp.digitalRead(sw3_1);
  btnPinState_SW3_2 = mcp.digitalRead(sw3_2);
  btnPinState_SW4_1 = mcp.digitalRead(sw4_1);
  btnPinState_SW4_2 = mcp.digitalRead(sw4_2);

  //************************************* Switch 1 ************************************//
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
          mcp.digitalWrite(CH1, Status_CH1);
          EEPROM.write(addrRelay1, 1);
          EEPROM.commit();
        }
        else
        {
          mcp.digitalWrite(CH1, Status_CH1);
          EEPROM.write(addrRelay1, 0);
          EEPROM.commit();
        }
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(20);
    }

    if (btnPinState_SW1_2 != lastButtonState_SW1_2)
    {
      if (btnPinState_SW1_2 == LOW)
      {

        Status_CH1 = !Status_CH1;
        Blynk.virtualWrite(V3, Status_CH1);

        if (Status_CH1 == 1)
        {
          mcp.digitalWrite(CH1, Status_CH1);
          EEPROM.write(addrRelay1, 1);
          EEPROM.commit();
        }
        else
        {
          mcp.digitalWrite(CH1, Status_CH1);
          EEPROM.write(addrRelay1, 0);
          EEPROM.commit();
        }
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(20);
    }
  }

  //************************************* Switch 2 ************************************//
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
          mcp.digitalWrite(CH2, Status_CH2);
          EEPROM.write(addrRelay2, 1);
          EEPROM.commit();
        }
        else
        {
          mcp.digitalWrite(CH2, Status_CH2);
          EEPROM.write(addrRelay2, 0);
          EEPROM.commit();
        }
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(20);
    }

    if (btnPinState_SW2_2 != lastButtonState_SW2_2)
    {
      if (btnPinState_SW2_2 == LOW)
      {

        Status_CH2 = !Status_CH2;
        Blynk.virtualWrite(V4, Status_CH2);
        if (Status_CH2 == 1)
        {
          mcp.digitalWrite(CH2, Status_CH2);
          EEPROM.write(addrRelay2, 1);
          EEPROM.commit();
        }
        else
        {
          mcp.digitalWrite(CH2, Status_CH2);
          EEPROM.write(addrRelay2, 0);
          EEPROM.commit();
        }
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(20);
    }
  }

  //************************************* Switch 3 ************************************//

  if (!is_boot3)
  {

    if (btnPinState_SW3_1 != lastButtonState_SW3_1)
    {
      if (btnPinState_SW3_1 == LOW)
      {

        Status_CH3 = !Status_CH3;
        Blynk.virtualWrite(V5, Status_CH3);
        if (Status_CH3 == 1)
        {
          mcp.digitalWrite(CH3, Status_CH3);
          EEPROM.write(addrRelay3, 1);
          EEPROM.commit();
        }
        else
        {
          mcp.digitalWrite(CH3, Status_CH3);
          EEPROM.write(addrRelay3, 0);
          EEPROM.commit();
        }
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(20);
    }

    if (btnPinState_SW3_2 != lastButtonState_SW3_2)
    {
      if (btnPinState_SW3_2 == LOW)
      {

        Status_CH3 = !Status_CH3;
        Blynk.virtualWrite(V5, Status_CH3);
        if (Status_CH3 == 1)
        {
          mcp.digitalWrite(CH3, Status_CH3);
          EEPROM.write(addrRelay3, 1);
          EEPROM.commit();
        }
        else
        {
          mcp.digitalWrite(CH3, Status_CH3);
          EEPROM.write(addrRelay3, 0);
          EEPROM.commit();
        }
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(20);
    }
  }

  //************************************* Switch 4 ************************************//

  if (!is_boot4)
  {

    if (btnPinState_SW4_1 != lastButtonState_SW4_1)
    {
      if (btnPinState_SW4_1 == LOW)
      {

        Status_CH4 = !Status_CH4;
        Blynk.virtualWrite(V6, Status_CH4);
        if (Status_CH4 == 1)
        {
          mcp.digitalWrite(CH4, Status_CH4);
          EEPROM.write(addrRelay4, 1);
          EEPROM.commit();
        }
        else
        {
          mcp.digitalWrite(CH4, Status_CH4);
          EEPROM.write(addrRelay4, 0);
          EEPROM.commit();
        }
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(20);
    }

    if (btnPinState_SW4_2 != lastButtonState_SW4_2)
    {
      if (btnPinState_SW4_2 == LOW)
      {

        Status_CH4 = !Status_CH4;
        Blynk.virtualWrite(V6, Status_CH4);
        if (Status_CH4 == 1)
        {
          mcp.digitalWrite(CH4, Status_CH4);
          EEPROM.write(addrRelay4, 1);
          EEPROM.commit();
        }
        else
        {
          mcp.digitalWrite(CH4, Status_CH4);
          EEPROM.write(addrRelay4, 0);
          EEPROM.commit();
        }
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(20);
    }
  }

  lastButtonState_SW1_1 = btnPinState_SW1_1;
  lastButtonState_SW1_2 = btnPinState_SW1_2;
  lastButtonState_SW2_1 = btnPinState_SW2_1;
  lastButtonState_SW2_2 = btnPinState_SW2_2;
  lastButtonState_SW3_1 = btnPinState_SW3_1;
  lastButtonState_SW3_2 = btnPinState_SW3_2;
  lastButtonState_SW4_1 = btnPinState_SW4_1;
  lastButtonState_SW4_2 = btnPinState_SW4_2;

  is_boot1 = false;
  is_boot2 = false;
  is_boot3 = false;
  is_boot4 = false;
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

void read_EEPROM()
{
  SaveRelay1 = EEPROM.read(addrRelay1);
  Serial.println("Status_CH1 = " + String(SaveRelay1));
  SaveRelay2 = EEPROM.read(addrRelay2);
  Serial.println("Status_CH2 = " + String(SaveRelay2));
  SaveRelay3 = EEPROM.read(addrRelay3);
  Serial.println("Status_CH3 = " + String(SaveRelay3));
  SaveRelay4 = EEPROM.read(addrRelay4);
  Serial.println("Status_CH4 = " + String(SaveRelay4));
  delay(2000);

}