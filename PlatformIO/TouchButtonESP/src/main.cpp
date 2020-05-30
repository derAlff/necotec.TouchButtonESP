/* Touch button firmware *
** Author:  Oliver Alff (necotec) **
** License: GPLv3 */

#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>

#define TOUCHTASTER   16 // define pin 16 (D0) as pin for the first touchpad
#define TOUCHTASTER2  14 // define pin 14 (D5) as pin for the second touchpad
#define TOUCHTASTER3  12 // define pin 12 (D6) as pin for the third touchpad
#define TOUCHTASTER4  13 // define pin 13 (D7) as pin for the fourth touchpad

#define TEST_LED      4 // define pin 4 (D2) as pin for the touchpad

String MqttFolder = ""; // the MQTT path
String MqttServerAddress = ""; // the MQTT Server

String DeviceWifiHostname = "Testdevice";  // the hostname for this device

const String WifiSsid = "";  // WIFI SSID
const String WifiPassword = ""; // WIFI password

bool RunCode = true;


bool led = false; // boolean for the led state

// function for led toggle
void toggleLed(bool state)
{
  if(state)
  {
    digitalWrite(TEST_LED, HIGH);
  }
  else
  {
    digitalWrite(TEST_LED, LOW);
  }

  Serial.print("State of the LED: ");
  Serial.println(state);
}

void setup() {
  // connect to WIFI
  if((WifiSsid != emptyString || WifiSsid != NULL) && (WifiPassword != emptyString || WifiPassword != NULL))
  {
    uint8_t wifiConnectCounter = 0;
    // take an output on serial console
    Serial.print("The WIFI SSID: ");
    Serial.println(WifiSsid);
    Serial.println("The WIFI SSID: ");
    Serial.println(WifiPassword);

    // connect to Wifi and take serial outputs
    WiFi.hostname(DeviceWifiHostname);
    Serial.println("Set Hostname to: " + DeviceWifiHostname);
    WiFi.begin(WifiSsid, WifiPassword);
    Serial.print("Connect to Wifi " + WifiSsid);
    Serial.print(".");
    while(WiFi.status() != WL_CONNECTED && wifiConnectCounter < 60)  // while no connection, print points to the console
    {
      Serial.print(".");
      delay(500);
      wifiConnectCounter++;
    }

    Serial.println();

    if(wifiConnectCounter >= 60)
    {
      RunCode = false;
    }
    if(RunCode){
      Serial.println("Wifi connected!");
    }
    else{
      Serial.println("Can not connect to Wifi! Timeout! Please check the connection options!");
    }
  }

  // set up the pins
  pinMode(TOUCHTASTER, INPUT);
  pinMode(TOUCHTASTER2, INPUT);
  pinMode(TOUCHTASTER3, INPUT);
  pinMode(TOUCHTASTER4, INPUT);
  pinMode(TEST_LED, OUTPUT);

  // toggle of the led by starting
  digitalWrite(TEST_LED, LOW);
  
  // begin a serial connection for output
  Serial.begin(9600);
  Serial.println("Program started.");
}

void loop() {
  if(RunCode)
  {
    // check the state of the pin and toggle
    if(digitalRead(TOUCHTASTER))
    {
      Serial.println("Welcome to the button part."); // give a feedback on serial console
      if(led)
      {
        led = false;
      }
      else{
        led = true;
      }
      
      Serial.print("Wait / debounce..."); // give more feedback on serial console
      while(digitalRead(TOUCHTASTER))
      {
        Serial.print("."); // give more more feedback on serial console
        delay(250);
      }
      Serial.println();
      toggleLed(led); // and now, toggle the led
    }
    else{
      Serial.println("Wifi is not connected. The code on this device do not running! Please check the options!");
      delay(1000);
    }
  }

  
}

