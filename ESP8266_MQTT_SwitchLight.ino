/*
   MQTT Light for Home-Assistant - NodeMCU (ESP8266)
   https://home-assistant.io/components/light.mqtt/

   Libraries :
    - ESP8266 core for Arduino : https://github.com/esp8266/Arduino
    - PubSubClient : https://github.com/knolleary/pubsubclient

   Sources :
    - File > Examples > ES8266WiFi > WiFiClient
    - File > Examples > PubSubClient > mqtt_auth
    - File > Examples > PubSubClient > mqtt_esp8266

   Schematic :
    - https://github.com/mertenats/open-home-automation/blob/master/ha_mqtt_light/Schematic.png
    - GND - LED - Resistor 220 Ohms - D1/GPIO5

   Configuration (HA) : 
    light:
      platform: mqtt
      name: Office light'
      state_topic: 'office/light1/status'
      command_topic: 'office/light1/switch'
      optimistic: false

   Samuel M. - v1.1 - 08.2016
   If you like this example, please add a star! Thank you!
   https://github.com/mertenats/open-home-automation
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MQTT_VERSION MQTT_VERSION_3_1_1

int buttonState1 = 1;
int lastButtonState1 = 1;
int buttonState2 = 1;
int lastButtonState2 = 1;
int buttonState3 = 1;
int lastButtonState3 = 1;

// Wifi: SSID and password
const char* WIFI_SSID = "ABC";
const char* WIFI_PASSWORD = "mothaibabon";

// MQTT: ID, server IP, port, username and password
const PROGMEM char* MQTT_CLIENT_ID = "office_light1";
const PROGMEM char* MQTT_SERVER_IP = "192.168.1.247";
const PROGMEM uint16_t MQTT_SERVER_PORT = 1883;
const PROGMEM char* MQTT_USER = "username";
const PROGMEM char* MQTT_PASSWORD = "matkhau";

// MQTT: topics
const char* MQTT_LIGHT_STATE_TOPIC1 = "house/light1/status";
const char* MQTT_LIGHT_COMMAND_TOPIC1 = "house/light1/switch";
const char* MQTT_LIGHT_STATE_TOPIC2 = "house/light2/status";
const char* MQTT_LIGHT_COMMAND_TOPIC2 = "house/light2/switch";
const char* MQTT_LIGHT_STATE_TOPIC3 = "house/light3/status";
const char* MQTT_LIGHT_COMMAND_TOPIC3 = "house/light3/switch";
const char* MQTT_LIGHT_STATE_TOPIC4 = "house/light4/status";
const char* MQTT_LIGHT_COMMAND_TOPIC4 = "house/light4/switch";

// payloads by default (on/off)
const char* LIGHT_ON = "ON";
const char* LIGHT_OFF = "OFF";

const PROGMEM uint8_t LED_PIN1 = 14;
const PROGMEM uint8_t LED_PIN2 = 12;
const PROGMEM uint8_t LED_PIN3 = 13;
const PROGMEM uint8_t LED_PIN4 = 16;
boolean m_light_state1 = false; // light is turned off by default
boolean m_light_state2 = false; // light is turned off by default
boolean m_light_state3 = false; // light is turned off by default
boolean m_light_state4 = false; // light is turned off by default

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void button1(){
  buttonState1 = digitalRead(5);
  if (buttonState1 != lastButtonState1) {
    if(m_light_state1 != true) {
    m_light_state1 = true;
    }
    else if(m_light_state1 != false) {
      m_light_state1 = false;
    }
  }
  lastButtonState1 = buttonState1;
  setLightState1();
  publishLightState1();
}
void button2(){
  buttonState2 = digitalRead(4);
  if (buttonState2 != lastButtonState2) {
    if(m_light_state2 != true) {
    m_light_state2 = true;
    }
    else if(m_light_state2 != false) {
      m_light_state2 = false;
    }
  }
  lastButtonState2 = buttonState2;
  setLightState2();
  publishLightState2();
}
void button3(){
  buttonState3 = digitalRead(0);
  if (buttonState3 != lastButtonState3) {
    if(m_light_state3 != true) {
    m_light_state3 = true;
    }
    else if(m_light_state3 != false) {
      m_light_state3 = false;
    }
  }
  lastButtonState3 = buttonState3;
  setLightState3();
  publishLightState3();
}

// function called to publish the state of the light (on/off)
void publishLightState1() {
  if (m_light_state1) {
    client.publish(MQTT_LIGHT_STATE_TOPIC1, LIGHT_ON, true);
  } else {
    client.publish(MQTT_LIGHT_STATE_TOPIC1, LIGHT_OFF, true);
  }
}
void publishLightState2() {
  if (m_light_state2) {
    client.publish(MQTT_LIGHT_STATE_TOPIC2, LIGHT_ON, true);
  } else {
    client.publish(MQTT_LIGHT_STATE_TOPIC2, LIGHT_OFF, true);
  }
}
void publishLightState3() {
  if (m_light_state3) {
    client.publish(MQTT_LIGHT_STATE_TOPIC3, LIGHT_ON, true);
  } else {
    client.publish(MQTT_LIGHT_STATE_TOPIC3, LIGHT_OFF, true);
  }
}
void publishLightState4() {
  if (m_light_state4) {
    client.publish(MQTT_LIGHT_STATE_TOPIC4, LIGHT_ON, true);
  } else {
    client.publish(MQTT_LIGHT_STATE_TOPIC4, LIGHT_OFF, true);
  }
}

// function called to turn on/off the light
void setLightState1() {
  if (m_light_state1) {
    digitalWrite(LED_PIN1, HIGH);
    Serial.println("INFO: Turn light on...");
  } else {
    digitalWrite(LED_PIN1, LOW);
    Serial.println("INFO: Turn light off...");
  }
}
void setLightState2() {
  if (m_light_state2) {
    digitalWrite(LED_PIN2, HIGH);
    Serial.println("INFO: Turn light on...");
  } else {
    digitalWrite(LED_PIN2, LOW);
    Serial.println("INFO: Turn light off...");
  }
}
void setLightState3() {
  if (m_light_state3) {
    digitalWrite(LED_PIN3, HIGH);
    Serial.println("INFO: Turn light on...");
  } else {
    digitalWrite(LED_PIN3, LOW);
    Serial.println("INFO: Turn light off...");
  }
}
void setLightState4() {
  if (m_light_state4) {
    digitalWrite(LED_PIN4, HIGH);
    Serial.println("INFO: Turn light on...");
  } else {
    digitalWrite(LED_PIN4, LOW);
    Serial.println("INFO: Turn light off...");
  }
}

// function called when a MQTT message arrived
void callback(char* p_topic, byte* p_payload, unsigned int p_length) {
  // concat the payload into a string
  String payload;
  for (uint8_t i = 0; i < p_length; i++) {
    payload.concat((char)p_payload[i]);
  }
  
  // handle message topic
  if (String(MQTT_LIGHT_COMMAND_TOPIC1).equals(p_topic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT_ON))) {
      if (m_light_state1 != true) {
        m_light_state1 = true;
        setLightState1();
        publishLightState1();
      }
    } else if (payload.equals(String(LIGHT_OFF))) {
      if (m_light_state1 != false) {
        m_light_state1 = false;
        setLightState1();
        publishLightState1();
      }
    }
  }
    if (String(MQTT_LIGHT_COMMAND_TOPIC2).equals(p_topic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT_ON))) {
      if (m_light_state2 != true) {
        m_light_state2 = true;
        setLightState2();
        publishLightState2();
      }
    } else if (payload.equals(String(LIGHT_OFF))) {
      if (m_light_state2 != false) {
        m_light_state2 = false;
        setLightState2();
        publishLightState2();
      }
    }
  }
    if (String(MQTT_LIGHT_COMMAND_TOPIC3).equals(p_topic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT_ON))) {
      if (m_light_state3 != true) {
        m_light_state3 = true;
        setLightState3();
        publishLightState3();
      }
    } else if (payload.equals(String(LIGHT_OFF))) {
      if (m_light_state3 != false) {
        m_light_state3 = false;
        setLightState3();
        publishLightState3();
      }
    }
  }
    if (String(MQTT_LIGHT_COMMAND_TOPIC4).equals(p_topic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT_ON))) {
      if (m_light_state4 != true) {
        m_light_state4 = true;
        setLightState4();
        publishLightState4();
      }
    } else if (payload.equals(String(LIGHT_OFF))) {
      if (m_light_state4 != false) {
        m_light_state4 = false;
        setLightState4();
        publishLightState4();
      }
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("INFO: Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("INFO: connected");
      // Once connected, publish an announcement...
      publishLightState1();
      publishLightState2();
      publishLightState3();
      publishLightState4();
      // ... and resubscribe
      client.subscribe(MQTT_LIGHT_COMMAND_TOPIC1);
      client.subscribe(MQTT_LIGHT_COMMAND_TOPIC2);
      client.subscribe(MQTT_LIGHT_COMMAND_TOPIC3);
      client.subscribe(MQTT_LIGHT_COMMAND_TOPIC4);
    } else {
      Serial.print("ERROR: failed, rc=");
      Serial.print(client.state());
      Serial.println("DEBUG: try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // init the serial
  Serial.begin(115200);

  // init the led
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  pinMode(LED_PIN4, OUTPUT);
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
  analogWriteRange(255);
  setLightState1();
  setLightState2();
  setLightState3();
  setLightState4();

  // init the WiFi connection
  Serial.println();
  Serial.println();
  Serial.print("INFO: Connecting to ");
  WiFi.mode(WIFI_STA);
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("INFO: WiFi connected");
  Serial.print("INFO: IP address: ");
  Serial.println(WiFi.localIP());

  // init the MQTT connection
  client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  button1();
  button2();
  button3();
  client.loop();
}
