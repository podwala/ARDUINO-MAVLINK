# Arduino MAVLink RGB LED Indicator

This project allows an Arduino to read MAVLink telemetry data from a drone flight controller and display the current flight mode using RGB LEDs.

## Features
- Reads MAVLink v1 serial frames
- Detects common flight modes
- RGB LED color indication
- Works with Arduino Uno

## Hardware Used
- Arduino Uno
- MAVLink Flight Controller (TELEM TX → Arduino RX)
- Common Cathode RGB LED
- 220Ω resistors

## Connections
- FC TX → Arduino RX (Pin 0)
- FC 5V → Arduino 5V
- FC GND → Arduino GND
- LED Red → Pin 9 (via resistor)
- LED Green → Pin 10 (via resistor)
- LED Blue → Pin 11 (via resistor)

## LED Colors
 Stabilize > Green 
 AltHold > Blue 
 Loiter > Cyan 
 Unknown > White 

## Baud Rate
57600 bps

## Author
Podwala
