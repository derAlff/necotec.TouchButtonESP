/* Touch button firmware *
** Author:  Oliver Alff (necotec) **
** License: GPLv3 */

#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "mqtt.h"

#define TOUCHTASTER   16 // define pin 16 (D0) as pin for the first touchpad
#define TOUCHTASTER2  14 // define pin 14 (D5) as pin for the second touchpad
#define TOUCHTASTER3  12 // define pin 12 (D6) as pin for the third touchpad
#define TOUCHTASTER4  13 // define pin 13 (D7) as pin for the fourth touchpad

#define TEST_LED      4  // define pin 4 (D2) as pin for the touchpad

#define MSG_BUFFER_SIZE   50
String DeviceWifiHostname = "";                   // the hostname for this device
const String WifiSsid = "your wifi ssid";           // WIFI SSID
const String WifiPassword = "your wifi password";   // WIFI password
String MacAddress = "";

// MQTT
const char* MqttTopic = "Zwischenraum/testTaster";    // the MQTT path
const char* MqttServerAddress = "192.168.10.34";      // the MQTT Server !!use ip address!!
uint16_t MqttPort = 1883;                             // the port of MQTT Server
WiFiClient WifiClient;
PubSubClient MqttClient(WifiClient);
unsigned long lastMsg = 0;
char msg[MSG_BUFFER_SIZE];
int value = 0;

const char* PublishTopic1 = "trigger"; 
const char* PublishTopic2; 
const char* PublishTopic3; 
const char* PublishTopic4;
const char* SubscribeTopic1;
const char* SubscribeTopic2; 
const char* SubscribeTopic3;
const char* SubscribeTopic4; 

bool RunCode = true;  //  if no connection to wifi, then don't run the program
 

bool led = false; // boolean for the led state

/* ****************** Functions ****************** */

// setup the wifi
void setup_wifi()
{
  delay(10);

  if((WifiSsid != emptyString || WifiSsid != NULL) && (WifiPassword != emptyString || WifiPassword != NULL))
  {
    uint8_t wifiConnectCounter = 0;
    // take an output on serial console
    Serial.print("The WIFI SSID: ");
    Serial.println(WifiSsid);
    Serial.println("The WIFI SSID: ");
    Serial.println(WifiPassword);

    // connect to Wifi and take serial outputs
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
      MacAddress = WiFi.macAddress();
      
      // Change Hostname
      String tempMacAddress = "";
      char tempChar;
      for(uint8_t i = 0; i < MacAddress.length(); i++)
      {
        tempChar = MacAddress[i];

        if(tempChar != ':')
        {
          tempMacAddress += tempChar;
        }
      }

      // Set hostname and print on serial console
      DeviceWifiHostname = "NCT-ESP-" + tempMacAddress;
      WiFi.hostname(DeviceWifiHostname);
      Serial.println("Set Hostname to: " + DeviceWifiHostname);
      Serial.println("MAC-Address of device: " + MacAddress);
    }
    else{
      Serial.println("Can not connect to Wifi! Timeout! Please check the connection options!");
    }
  }
}

// setup MQTT
void setup_mqtt()
{

}

// MQTT reconnect
void mqttReconnect()
{
  while(!MqttClient.connected())
  {
    Serial.print("Reconnect to MQTT-broker...");
    if(MqttClient.connect("EspClient"))
    {
      Serial.print("Connected to MQTT-broker.");
    }
    else{
      Serial.print("Failed to connect. State: ");
      Serial.println(MqttClient.state());
      Serial.print("Trying reconnect in 5 seconds.");
      delay(5000);
    }
  }
}

// function for led toggle
void toggleLed(bool state)
{
  if(state)
  {
    digitalWrite(TEST_LED, HIGH);
    MqttClient.publish(MqttTopic,PublishTopic1);
  }
  else
  {
    digitalWrite(TEST_LED, LOW);
    MqttClient.publish(MqttTopic,PublishTopic1);
  }

  Serial.print("State of the LED: ");
  Serial.println(state);
}

/* **************** End functions **************** */

void setup() {
  // begin a serial connection for output
  Serial.begin(9600);
  Serial.println("Program started.");

  // set up the pins
  pinMode(TOUCHTASTER, INPUT);
  pinMode(TOUCHTASTER2, INPUT);
  pinMode(TOUCHTASTER3, INPUT);
  pinMode(TOUCHTASTER4, INPUT);
  pinMode(TEST_LED, OUTPUT);

  // toggle of the led by starting
  digitalWrite(TEST_LED, LOW);

  // connect to WIFI
  setup_wifi();
  MqttClient.setServer(MqttServerAddress, MqttPort);
}

void loop() {
  if(RunCode)
  {
    // check MQTT connection
    if(!MqttClient.connected())
    {
      mqttReconnect();
      Serial.println("State of \"MqttClient\"" + MqttClient.connected());
    }
    MqttClient.loop();

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
  }
  else
  {
    Serial.println("Wifi is not connected. The code on this device do not running! Please check the options!");
    delay(1000);
  }
}

