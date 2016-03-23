# edison_interface
Clone of Primo Interface Board for use with Edison robot.

# Requirements
* Arduino Mega 2560
* IRremote library - https://github.com/z3t0/Arduino-IRremote
* IR LED
* 200R, 2.2kR, 100kR resistors for control blocks
* Status LED
* Button
* Edison robot

# Usage
Hook up the required components to the Mega
* Digital pin 2 - Start button (input pullup)
* Digital pin 4 - Status LED
* Digital pin 9 - IR LED
* Analog pins 0-15 - Control block resistors

Use the Remote Control Driving programming strips for the Edison to program it to drive according to the resistors connected to the analog pins on the Mega.
