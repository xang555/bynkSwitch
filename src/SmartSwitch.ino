#define BLYNK_PRINT Serial

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

String EEPROM_read(int index, int length) {
  String text = "";
  char ch = 1;

  for (int i = index; (i < (index + length)) && ch; ++i) {
    if (ch = EEPROM.read(i)) {
      text.concat(ch);
    }
  }
  return text;
}

int EEPROM_write(int index, String text) {
  for (int i = index; i < text.length() + index; ++i) {
    EEPROM.write(i, text[i - index]);
  }
  EEPROM.write(index + text.length(), 0);
  EEPROM.commit();

  return text.length() + 1;
}

void setup()
{

  Serial.begin(115200); //Start serial for output
  mcp.begin();          // use default address 0
  delay(100);
  EEPROM.begin(512);
  delay(1000);
  Serial.println();
  read_EEPROM();
  delay(1000);
  Serial.println();
  Serial.println();
  Serial.println();
  config_Pin();


  Status_CH1 = SaveRelay1 == "1" ? 1 : 0;
  Status_CH2 = SaveRelay2 == "1" ? 1 : 0;
  // Status_CH3 = SaveRelay3 == "1" ? 1 : 0;
  // Status_CH4 = SaveRelay4 == "1" ? 1 : 0;

  mcp.digitalWrite(CH1, Status_CH1);
  delay(100);
  mcp.digitalWrite(CH2, Status_CH2);


  connectWiFi();
  connectBlynk();
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, checkPhysicalButton);

  // mcp.digitalWrite(CH3, Status_CH3);
  // mcp.digitalWrite(CH4, Status_CH4);
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
    EEPROM_write(addrRelay1, "1");
    delay(50);
  }
  else
  {
    mcp.digitalWrite(CH1, LOW);
    EEPROM_write(addrRelay1, "0");
    delay(50);
  }
}

BLYNK_WRITE(V4)
{ // Map this Virtual Pin to your  Mobile Blynk apps widget.
  Status_CH2 = param.asInt();

  if (Status_CH2 == 1)
  {
    mcp.digitalWrite(CH2, HIGH);
    EEPROM_write(addrRelay2, "1");
    delay(50);
  }
  else
  {
    mcp.digitalWrite(CH2, LOW);
    EEPROM_write(addrRelay2, "0");
    delay(50);
  }
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
          EEPROM_write(addrRelay1, "1");
          delay(50);
        }
        else
        {
          mcp.digitalWrite(CH1, Status_CH1);
          EEPROM_write(addrRelay1, "0");
          delay(50);
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
          EEPROM_write(addrRelay1, "1");
          delay(50);
        }
        else
        {
          mcp.digitalWrite(CH1, Status_CH1);
          EEPROM_write(addrRelay1, "0");
          delay(50);
        }
      }
      else
      {
      }
      // Delay a little bit to avoid bouncing
      delay(20);
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
          mcp.digitalWrite(CH2, Status_CH2);
          EEPROM_write(addrRelay2, "1");
          delay(50);
        }
        else
        {
          mcp.digitalWrite(CH2, Status_CH2);
          EEPROM_write(addrRelay2, "0");
          delay(50);
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
          EEPROM_write(addrRelay2, "1");
          delay(50);
        }
        else
        {
          mcp.digitalWrite(CH2, Status_CH2);
          EEPROM_write(addrRelay2, "0");
          delay(50);
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

void read_EEPROM()
{
  SaveRelay1 = EEPROM_read(addrRelay1, 1);
  delay(1500);
  Serial.println(SaveRelay1);
  SaveRelay2 = EEPROM_read(addrRelay2, 1);
  delay(1500);
  Serial.println(SaveRelay2);
  // SaveRelay3 = EEPROM_read(addrRelay3, 5);
  // SaveRelay4 = EEPROM_read(addrRelay4, 5);
}