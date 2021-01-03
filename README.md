# Garage heating control with ESP8266

## History

one garage with 220V, one heating floor 440W, one air heater 750W, one wifi router, one android phone, one cloud provider account.




## Prerequisites:

*Hardware*
- ESP8266 + wifi 2.4GHz internet access
- DHT11 sensor module (air temperature / humidity)
- DS18B20 DallasTemperature sensor waterproof module **x3**
- 4K7 Ohms Resistor 
- 5K1 Ohms Resistor 
- Relay module **x2**
- Wiring cables and outlets

*Sketch*
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
- MQTT Dash


## TODO ##

*Features-on-go*
- ~~repub mode~~
- ~~pub floormax/floormin values~~
- reformat acls
- ~~add poweroff timer for heater~~
- add more fail checks

*Hardware*
 - ~~add 2 more Dallas sensors (external temperature and underfloor temperature)~~
 - ~~add 1 more relay for external heater (air humidifer)~~

*Graphs*
- **node red** 
- mqtt export to (take one)
- vm/prom/influx
- grafana 

*Automation*
- atutomation of broker deployment/software installation
- compile and build .ino no gui
