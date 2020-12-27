# Garage heating control with ESP8266

## Board prerequisites:

*Hardware:*
- ESP8266
- DHT11 sensor/module
- DS18B20 DallasTemperature module
- 4K7 Ohms Resistor x2
- Wiring cables

*Software*
- Arduino IDE with ESP8266 board library installed 
- ESP8266WiFi.h
- PubSubClient.h
- DHT.h 
needs Adafruit Unified Sensor library
- DallasTemperature.h
needs OneWire.h library


*MQTT BROKER*
- linux vps
- mosquitto binary / acl setup

*MQTT Client Android*
- MQTT Dash

## TODO ##

*Graphs*
- tsdb export 
- grafana / node_red ?
