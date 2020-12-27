# Garage heating control with ESP8266

## Prerequisites:

*Hardware:*
- ESP8266 + wifi 2.4GHz internet access
- DHT11 sensor/module (air temperature / humidity)
- DS18B20 DallasTemperature module (upfloor temperature)
- 4K7 Ohms Resistor x2 
- Relay module 
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
- linux vps accessible ip
- mosquitto.service
- acl anonymous pub

*MQTT Client Android*
* MQTT Dash
** floor mode
** min temp
** max temp

## TODO ##

*Features-on-go*
- repub mode 
- pub floormax/floormin values 
- reformat acls

*Hardware*
 - add 2 more Dallas sensors (external temperature and underfloor temperature)
 - add 1 more relay for external heater (air humidifer)

*Graphs*
- tsdb export 
- grafana / node_red ?

*Automation*
- terraform
- build and test cpp from .ino (jinja2)
