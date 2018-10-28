// #define BLYNK_PRINT Serial
// #define DEV_Mode

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Wire.h>
#include <EEPROM.h>
#include "Adafruit_MCP23017.h"
#include "Registor.h"
#include "image.h"

char auth[] = "2762bbedfc99417592d8bd9421b5b319"; // switch_002
char My_DOMAIN[] = "cloud.laoio.la";

#define My_PORT 8080
#define Connect__WiFi 2
#define ConfigWiFi_Pin 12

SimpleTimer timer;
Adafruit_MCP23017 mcp;

WiFiClient wifiClient;

#define ESP_AP_NAME "WiFI Config"

int counter = 0;

// This function tries to connect to the cloud using TCP
void connectWifiAndBlynk()
{

#ifdef DEV_Mode
  Serial.println(WiFi.SSID());
  Serial.println(WiFi.psk());
#endif

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    timer.run();
    Serial.print(".");
  }
  Serial.println();

  Blynk.config(auth, My_DOMAIN, My_PORT);
}

BLYNK_CONNECTED()
{
  // Alternatively, you could override server state using:
  Blynk.virtualWrite(V1, Status_CH1);
  Blynk.virtualWrite(V2, Status_CH2);
  Blynk.virtualWrite(V3, Status_CH3);
  Blynk.virtualWrite(V4, Status_CH4);
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
  Blynk.syncVirtual(V4);
}

BLYNK_WRITE(V1)
{ // Map this Virtual Pin to your  Mobile Blynk apps widget.
  Status_CH1 = param.asInt();

  if (Status_CH1 == 1)
  {
    mcp.digitalWrite(CH1, Status_CH1);
#ifdef DEV_Mode
    Serial.println("CH1 = " + String(Status_CH1));
#endif

    EEPROM.write(addrRelay1, 1);
    EEPROM.commit();
  }
  else
  {
    mcp.digitalWrite(CH1, Status_CH1);
#ifdef DEV_Mode
    Serial.println("CH1 = " + String(Status_CH1));
#endif
    EEPROM.write(addrRelay1, 0);
    EEPROM.commit();
  }
}

BLYNK_WRITE(V2)
{ // Map this Virtual Pin to your  Mobile Blynk apps widget.
  Status_CH2 = param.asInt();

  if (Status_CH2 == 1)
  {
    mcp.digitalWrite(CH2, Status_CH2);
#ifdef DEV_Mode
    Serial.println("CH2 = " + String(Status_CH2));
#endif
    EEPROM.write(addrRelay2, 1);
    EEPROM.commit();
  }
  else
  {
    mcp.digitalWrite(CH2, Status_CH2);
#ifdef DEV_Mode
    Serial.println("CH2 = " + String(Status_CH2));
#endif
    EEPROM.write(addrRelay2, 0);
    EEPROM.commit();
  }
}

BLYNK_WRITE(V3)
{ // Map this Virtual Pin to your  Mobile Blynk apps widget.
  Status_CH3 = param.asInt();

  if (Status_CH3 == 1)
  {
    mcp.digitalWrite(CH3, Status_CH3);
#ifdef DEV_Mode
    Serial.println("CH3 = " + String(Status_CH3));
#endif
    EEPROM.write(addrRelay3, 1);
    EEPROM.commit();
  }
  else
  {
    mcp.digitalWrite(CH3, Status_CH3);
#ifdef DEV_Mode
    Serial.println("CH3 = " + String(Status_CH3));
#endif
    EEPROM.write(addrRelay3, 0);
    EEPROM.commit();
  }
}

BLYNK_WRITE(V4)
{ // Map this Virtual Pin to your  Mobile Blynk apps widget.
  Status_CH4 = param.asInt();

  if (Status_CH4 == 1)
  {
    mcp.digitalWrite(CH4, Status_CH4);
#ifdef DEV_Mode
    Serial.println("CH4 = " + String(Status_CH4));
#endif
    EEPROM.write(addrRelay4, 1);
    EEPROM.commit();
  }
  else
  {
    mcp.digitalWrite(CH4, Status_CH4);
#ifdef DEV_Mode
    Serial.println("CH4 = " + String(Status_CH4));
#endif
    EEPROM.write(addrRelay4, 0);
    EEPROM.commit();
  }
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
        Blynk.virtualWrite(V1, Status_CH1);

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
      delay(50);
    }

    if (btnPinState_SW1_2 != lastButtonState_SW1_2)
    {
      if (btnPinState_SW1_2 == LOW)
      {

        Status_CH1 = !Status_CH1;
        Blynk.virtualWrite(V1, Status_CH1);

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
      delay(50);
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
        Blynk.virtualWrite(V2, Status_CH2);
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
      delay(50);
    }

    if (btnPinState_SW2_2 != lastButtonState_SW2_2)
    {
      if (btnPinState_SW2_2 == LOW)
      {

        Status_CH2 = !Status_CH2;
        Blynk.virtualWrite(V2, Status_CH2);
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
      delay(50);
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
        Blynk.virtualWrite(V3, Status_CH3);
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
      delay(50);
    }

    if (btnPinState_SW3_2 != lastButtonState_SW3_2)
    {
      if (btnPinState_SW3_2 == LOW)
      {

        Status_CH3 = !Status_CH3;
        Blynk.virtualWrite(V3, Status_CH3);
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
      delay(50);
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
        Blynk.virtualWrite(V4, Status_CH4);
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
      delay(50);
    }

    if (btnPinState_SW4_2 != lastButtonState_SW4_2)
    {
      if (btnPinState_SW4_2 == LOW)
      {

        Status_CH4 = !Status_CH4;
        Blynk.virtualWrite(V4, Status_CH4);
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
      delay(50);
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
  SaveRelay2 = EEPROM.read(addrRelay2);
  SaveRelay3 = EEPROM.read(addrRelay3);
  SaveRelay4 = EEPROM.read(addrRelay4);

#ifdef DEV_Mode
  Serial.println("Status_CH1 = " + String(SaveRelay1));
  Serial.println("Status_CH2 = " + String(SaveRelay2));
  Serial.println("Status_CH3 = " + String(SaveRelay3));
  Serial.println("Status_CH4 = " + String(SaveRelay4));
#endif

  delay(2000);
}

void setup()
{

  Serial.begin(115200); //Start serial for output
  EEPROM.begin(512);
  mcp.begin(); // use default address 0
  delay(100);
  Serial.println();
  Serial.println();
  Serial.println();

  read_EEPROM();
  delay(100);

  pinMode(Connect__WiFi, OUTPUT);
  pinMode(ConfigWiFi_Pin, INPUT_PULLUP);
  config_Pin();

  Status_CH1 = SaveRelay1 == 1 ? 1 : 0;
  Status_CH2 = SaveRelay2 == 1 ? 1 : 0;
  Status_CH3 = SaveRelay3 == 1 ? 1 : 0;
  Status_CH4 = SaveRelay4 == 1 ? 1 : 0;

  WiFi.mode(WIFI_STA);

  delay(1000);

  while (digitalRead(ConfigWiFi_Pin) == LOW) // Press button
  {
    counter++;

    if (counter == 200)
    {
      WiFiManager wifiManager;
      digitalWrite(Connect__WiFi, HIGH);
      delay(100);
      digitalWrite(Connect__WiFi, LOW);
      delay(100);
      digitalWrite(Connect__WiFi, HIGH);
      delay(100);
      digitalWrite(Connect__WiFi, LOW);
      delay(100);
      digitalWrite(Connect__WiFi, HIGH);
      delay(100);
      digitalWrite(Connect__WiFi, LOW);
      delay(100);
      wifiManager.setCustomHeadElement(IMAGE_DATA.c_str());
      wifiManager.startConfigPortal(ESP_AP_NAME);
      counter = 0;
    }
  }

  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  mcp.digitalWrite(CH1, Status_CH1);
  mcp.digitalWrite(CH2, Status_CH2);
  mcp.digitalWrite(CH3, Status_CH3);
  mcp.digitalWrite(CH4, Status_CH4);
  timer.setInterval(100L, checkPhysicalButton);
  connectWifiAndBlynk(); // conect wifi and blynk server
}

void loop()
{

  Blynk.run();
  yield();
  timer.run();
  yield();

  if (Blynk.connected())
  {
    digitalWrite(Connect__WiFi, HIGH);
  }
  else
  {
    digitalWrite(Connect__WiFi, LOW);
  }

  yield();
}
