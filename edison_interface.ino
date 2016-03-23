// primo cubetto interface board clone for edison
// made for arduino mega

// wiring:
// -analog pins 0-15 input pullup for command blocks
// -digital pin 9 outputs to IR led for communication with edison
// -digital pin 2 inputs the go button

#include <IRremote.h>

IRsend irsend;

// analog pins are used to read command blocks
static const uint8_t analogPins[] = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15};

// analogRead values for resistors
// in sequence:
// forward - 200R
// left - 2.2kR
// right - 100kR
static const uint16_t resistorValues[] = {20,72,752};
static const uint8_t tolerance = 10;

// IR codes in same sequence as resistor values
static const unsigned long IRcodes[] = {0xA90, 0xB90, 0xC90};

// digital pin used for button
static const uint8_t goButton = 2;
uint8_t buttonState;

// digital pin used for status LED
static const uint8_t statusLED = 4;

// send IR burst (one command)
void cmdBurst(int times, unsigned long data) {
  for(int i = 1; i < times; i++) {
    irsend.sendSony(data, 12);
    delay(20);
  }
}

// read resistor values and output IR
void parseProgram() {
  for (int i = 0; i < 16; i++) {
    uint16_t value = analogRead(i);
    
    Serial.print(i);
    Serial.print(": ");
    Serial.println(value);
    
    // iterate over known resistor values
    for(int r = 0; r < 3; r++) {
      // check if value is within tolerance range of known value
      if(resistorValues[r] - tolerance < value && resistorValues[r] + tolerance > value) {
        // output corresponding IR code
        cmdBurst(4, IRcodes[r]);
        
        // 1 second between each instruction
        delay(1000);        
      }
    }
  }
}

void setup() {
  // IR output pin is set by library
  // set all input pins
  for(int i = 0; i < 16; i++) {
    pinMode(analogPins[i], INPUT_PULLUP);
  }
  pinMode(goButton, INPUT_PULLUP);
  
  // set LED output
  pinMode(statusLED, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // wait for button, don't repeat if button was already pressed
  if(digitalRead(goButton) == LOW && buttonState == 0) {
    buttonState = 1;
    digitalWrite(statusLED, HIGH);
    parseProgram();
    digitalWrite(statusLED, LOW);
  } else if(digitalRead(goButton) == HIGH && buttonState == 1) {
    buttonState = 0;
  }
  
  delay(50);
}
