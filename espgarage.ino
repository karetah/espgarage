/*
  ESP-8266 Garage Control
  https://github.com/karetah/espgarage
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
//#define RELAY1 LED_BUILTIN // 2 (D4) pulled output is inverted
#define RELAY1 14 //D5
#define RELAY2 12 //D6
  // GPIO where the DS18B20 is connected to
#define ONEWIREPIN 4 //D2
#define TEMPERATURE_PRECISION 10
#define DHTPIN 5 // D1
#define DHTTYPE DHT11 // DHT 11
// #define DHTTYPE    DHT22     // DHT 22 (AM2302)
// #define DHTTYPE    DHT21     // DHT 21 (AM2301)
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

const char *ssid = "wifinetwork";
const char *password = "wifipassword0";
const char *mqtt_server = "broker.kareta.ru";


unsigned long lastSecond = 0;
unsigned long lastSecond5 = 0;
unsigned long now;

float h; // DHT Humidity
float t; // DHT Temperature
float d0; // DS18B20 index 0 Temperature
float d1; // DS18B20 index 0 Temperature
float d2; // DS18B20 index 0 Temperature
int stateR1=0; // Relay 1 state (floor switch)
int stateR2=0; // Relay 2 state (heater switch)
int mode; // Operating mode
int dmax; // Floor max (27-30 C)
int dmin; // Floor min (2-3 C)
int tmax; 
int tmin;
const char *modetopic = "myesp/relay/mode";
const char *tmintopic = "myesp/relay/tmin";
const char *tmaxtopic = "myesp/relay/tmax";
const char *d0topic = "myesp/sensors/d0";
const char *d1topic = "myesp/sensors/d1";
const char *d2topic = "myesp/sensors/d2";
const char *ttopic = "myesp/sensors/t";
const char *htopic = "myesp/sensors/h";
const char *r1topic = "myesp/relay/1";
const char *r2topic = "myesp/relay/2";
String clientId = "myesp-";

WiFiClient espClient;
PubSubClient client(espClient);
OneWire oneWire(ONEWIREPIN);
DallasTemperature sensors(&oneWire);
DHT dht(DHTPIN, DHTTYPE);


//DeviceAddress d0address, d1address, d2address ;
DeviceAddress d0address = { 0x28, 0x08, 0x0E, 0x45, 0x92, 0x0D, 0x02, 0x2E };
DeviceAddress d1address = { 0x28, 0xE2, 0x94, 0x77, 0x91, 0x08, 0x02, 0x96 };
DeviceAddress d2address = { 0x28, 0x59, 0x16, 0x45, 0x92, 0x12, 0x02, 0x81 };


void reconnect()
{
  if (!client.connected())
  {
    // Serial.print("Attempting MQTT connection...");
   // Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      client.subscribe(modetopic);
      client.subscribe(tmaxtopic);
      client.subscribe(tmintopic);      
      client.subscribe(r2topic); 
    }
    else
    {
      // Serial.print("failed, rc=");
      // Serial.print(client.state());
      // Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying§
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  String intPayload = "";
  for (unsigned int i = 0; i < length; i++) {
    intPayload += ((char)payload[i]);
  }
  String inTopic(topic);
  String modeTopic(modetopic);
  String maxTopic(tmaxtopic);
  String minTopic(tmintopic);
  String r2Topic(r2topic);
          // Serial.print("current mode: ");
          // Serial.println(mode);

// i dont't know to compare the topic pointers except comparing strings.
    if (inTopic == modeTopic) 
        {
        //    Serial.println(int(payload[0]));
        //  mode = payload[0] - 48;
          mode = intPayload.toInt();
          // Serial.print("new mode: ");
          // Serial.println(mode);
        }
    else if (inTopic == r2Topic) {
            stateR2 = intPayload.toInt();
          Serial.print("new mode: ");
          Serial.println(mode);
             }

    else
       if (mode == 3) {
          if (inTopic == maxTopic) {
            dmax = intPayload.toInt();
            // Serial.print("manual: maxtemp: ");
            // Serial.println(dmax);
            // Serial.println(intPayload);
          }
          else if (inTopic == minTopic) {
            dmin = intPayload.toInt();
            // Serial.print("manual: mintemp: ");
            // Serial.println(dmin);
            // Serial.println(intPayload);
          }
          else 
          {
            // Serial.print("wrong topic: ");
            // Serial.println(topic);
          }
      }
      else 
        {
    
             
            // Serial.print("manual: maxtemp: ");
            // Serial.println(dmax);
            // Serial.println(intPayload);
          }
        // Serial.print("Wrong mode: ");
        // Serial.println(mode);
        

    intPayload = "";
  
}

// for future use
// void getManual(){

// }

int dutyMode(int dM){
  // hardcoded values for various modes
  switch (dM){
    case 1:
      dmin = 24;
      dmax = 27;
      tmin = 10;
      tmax = 15;
      return 1;
    case 2:
      dmin = 5;
      dmax = 10;
      tmin = 2;
      tmax = 5;
      return 2;
    case 3:
 //     getManual();
      return 3;
    default:
      dmin = 2;
      dmax = 5;
      tmin = 1;
      tmax = 3;
      return 0;
  }
}

int CR1(int m) {
    switch (m){
      case 1:
        digitalWrite(RELAY1, 1);
        return 1;  
      default:
        digitalWrite(RELAY1, 0);
        return 0;
    }
}

int CR2(int n) {
    switch (n){
      case 1:
        digitalWrite(RELAY2, 1);
        return 1;  
      default:
        digitalWrite(RELAY2, 0);
        return 0;
    }
}
void getSensorTest(){
  // simulate temperature response from relay condition
    if (stateR1 == 1) d0++;
    else d0--;
}

void getSensorsAll(){
    sensors.requestTemperatures();
    h = dht.readHumidity();
    t = dht.readTemperature();
    delay(10);
    d0 = sensors.getTempC(d0address);
    delay(10);
    d1 = sensors.getTempC(d1address);
    delay(10);
    d2 = sensors.getTempC(d2address);
    delay(10);
    if(d2 == DEVICE_DISCONNECTED_C) d2 = 127;
  
}


void PublishData(){
      // Publish section
    Serial.print("dallas0 temp: ");
    Serial.println(d0);
    Serial.print("dallas1 temp: ");
    Serial.println(d1);
    Serial.print("dallas2 temp: ");
    Serial.println(d2);
    // Serial.print("R1 state: ");
    // Serial.println(stateR1);
    // Serial.print("duty mode: ");
    // Serial.println(mode);
    snprintf(msg, MSG_BUFFER_SIZE, "%f", d0);
    client.publish(d0topic, msg);
    snprintf(msg, MSG_BUFFER_SIZE, "%f", d1);
    client.publish(d1topic, msg);
    snprintf(msg, MSG_BUFFER_SIZE, "%f", d2);
    client.publish(d2topic, msg);
    // Serial.print("publish dallas0: ");
    // Serial.println(msg);
    snprintf(msg, MSG_BUFFER_SIZE, "%f", t);
    client.publish(ttopic, msg);
    // Serial.print("publish dht temp: ");
    // Serial.println(msg);
    snprintf(msg, MSG_BUFFER_SIZE, "%f", h);
    client.publish(htopic, msg);
    // Serial.print("publish dht humd: ");
    // Serial.println(msg);
    snprintf(msg, MSG_BUFFER_SIZE, "%i", stateR1);
    client.publish(r1topic, msg);
    snprintf(msg, MSG_BUFFER_SIZE, "%i", stateR2);
    client.publish(r2topic, msg);
    // Serial.print("publish relay 1 state: ");
    // Serial.println(msg);
    snprintf(msg, MSG_BUFFER_SIZE, "%i", mode);
    client.publish(modetopic, msg);
    snprintf(msg, MSG_BUFFER_SIZE, "%i", dmax);
    client.publish(tmaxtopic, msg);
    snprintf(msg, MSG_BUFFER_SIZE, "%i", dmin);
    client.publish(tmintopic, msg);
    // // Serial.println(msg);
}


void setup()
{
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  delay(10);
  dht.begin();
  sensors.begin();
  sensors.setResolution(d0address, TEMPERATURE_PRECISION);
  sensors.setResolution(d1address, TEMPERATURE_PRECISION);
  sensors.setResolution(d2address, TEMPERATURE_PRECISION);

  // Create a random client ID
  randomSeed(micros());
  // clientId += String(random(0xffff), HEX);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  mode = dutyMode(0);

}

void loop()
{
  mode = dutyMode(mode);
  now = millis();
  if (WiFi.status() == WL_CONNECTED) 
    {
    if (!client.connected())  reconnect();
    client.loop();
    }




// 1 second run
  if (now - lastSecond > 2000) 
  {
    // Get sensors data every second
    getSensorsAll();
    // ..or simulate getting data
    // getSensorTest();
//    Serial.println(stateR2);
    lastSecond = now;
  }
  // Every 5 seconds publish data
  if (now - lastSecond5 > 5000) 
  {
    PublishData();
    lastSecond5 = now;
  }

// main RELAY1 logic
  
  if (stateR1 == 1 && int(d2) > dmax) stateR1 = CR1(!stateR1);
  else if (stateR1 == 0 && int(d2) < dmin) stateR1 = CR1(!stateR1);
  else CR1(stateR1);

stateR2 = CR2(stateR2); 
}
