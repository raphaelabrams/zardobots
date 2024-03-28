# zardobots
simple robots for fun


# code 

## Hello world
Start here! Blink an LED. This will verify that we have a working toolchain.

## Button test
add a button to test input functionality

## servo test
Attach the battery wires, with branch for servo
move a servo through a full range of angles, calibrate if needed

## Time timer
Timer system to show time. Time is the deal here. Like a Time Timer but with a more inscrutable interface.


## Monitor sensor
Attach the analog sensor
Test analog input and serial debug output

## Light Follower
Uses two LDR sensors in voltage divider configuration to generate an analog signal proportional to the illumination difference between them. With an error correction loop a servo can be used to steer the sensor pod toward or away from a light source.

## Zardoz! (bonus round)
Use digital signal filters and a microphone input to control the wobbling head and glowing eyes of everyone's favorite late stage post futuristic floating apocalyptic murder idol.




# Schedule:
### install, setup, intros, settle in
Here's a link to the guide from Seeed in case there's trouble getting things working
https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/
### solder an LED and resistor
use "Hello World" code
### solder a button
use "button test" code
### solder a servo and battery cable to board
use "servo test" code
### attach photocells to servo horn (ladyhead or paddle), solder to board
use "monitor sensor" code, serial monitor or graph
use "light follower" code, work with defines to tweak
### time to decorate and mess with code
### if there's any time left, we can do a few zardoz units, have a whistling party



# The Rest
## 3D files
These are the STL files you can use to print out more parts if you like.  

## Schematics
Diagrams to show electrical connections for each project


# Partial BOM
Arduino: https://www.mouser.com/ProductDetail/713-113991054

Servo: https://www.mouser.com/ProductDetail/426-SER0053

LDR: NTE part# 02-LDR23

Alarmingly cheap microphone with preamp: https://www.amazon.com/dp/B00XT0PH10?psc=1&ref=ppx_yo2ov_dt_b_product_details

Battery: YDL 102050 https://ydlbattery.com/products/3-7v-1000mah-102050-lithium-polymer-ion-battery?variant=42093651787929

JST-PH 2.0 cable for battery: https://www.amazon.com/dp/B07NWNPB77?psc=1&ref=ppx_yo2ov_dt_b_product_details

