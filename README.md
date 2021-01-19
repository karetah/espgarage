# Garage heating control with ESP8266

## History

~~one garage with 220V, one heating floor 440W, one air heater 750W, one wifi router, one android phone, one cloud provider account.~~

Ok...

I have a concrete garage, sized 3 x 6 m

The walls is covered with the "Vagonka" wood, maiden by the previous owner. (I don't know what is between its, perhaps air, oh yes!)

The ceiling is the concrete plates, the roof is not leaking.

The entry gate is the metal pipes welded folded fullmetal plates

The garage's floor was filled with a concrete at the base level.



Floor insulation:

- First level is a thin steam insulation cover.
- Second level is a 20mm "Penoplex" thermal insulation plates.
- Third level is a 8mm plywood.
- Fourth level depth is a ~3-5mm thermal insulation. At the bottom of heating surface, it is the special type of mat, elsewhere there is a foiled mat.
- Next, thin infra-red heating mat, and the finally, 
- Laminate flooring. 

Ceiling insulation:

- 30mm "Penoplex" plates (glued to concrete)

Gates insulation:

- 20mm "Penoplex" glued to metal plates at the door side
- 30mm 

## Prerequisites:

*Hardware*
- ESP8266 + wifi 2.4GHz internet access
- DHT11 sensor module (air temperature / humidity)
- DS18B20 DallasTemperature sensor waterproof module **at least one**
- 4K7 Ohms Resistor 
- 5K1 Ohms Resistor 
- Relay module **at least one**
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

*Features*
- add more documentation
- reformat acls/add more security
- ~~add poweroff timer for heater~~
- ~~add more fail checks~~
- relative temperature mode

*Hardware*
 - ~~add 2 more Dallas sensors (external temperature and underfloor temperature)~~
 - ~~add 1 more relay for external heater (air humidifer)~~

*Graphs*
- ~~node red~~ 
- mqtt export to (take one)
- vm/prom/influx
- grafana 

*Automation*
- atutomation of broker deployment/software installation
- compile and build .ino no gui
