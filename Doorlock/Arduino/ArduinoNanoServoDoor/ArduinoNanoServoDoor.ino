// **************************************************************************
//   ArduinoNanoServoDoor.ino - Change servo position based on UART input   *
// **************************************************************************
//
// Written by Simen Stensås and Kjell Kirkaune,
// for ELE3391 Elektro prosjekt in the fall of 2019 at NTNU in Gjøvik.
//
// For controlling a door with a servo using transciever UART read to an Arduino Nano.
//
// *********************************************************************


#include <Servo.h>            // Use Servo library, included with IDE
#include <SPI.h>              // UART/SPI
#include <Wire.h>
#define LOCKED_POS 135        // Defining positions
#define OPEN_POS  0

Servo myServo;                // Create Servo object to control the servo
int led = 4;                  // LED connected at digital pin 4

void setup() {
  Serial.begin(9600);         //For debugging
  myServo.attach(3);          // Servo is connected to digital pin 3
  pinMode(led, OUTPUT);       // PORT 4 set as output
}

void loop() {
  if(Serial.available())      // Check for availablity of data at Serial Port
  {
    int data = Serial.read(); // Reading Serial Data and saving in data variable

    switch(data) {
      case 0:                 // IQRF is telling arduino that door should be locked
        digitalWrite(led, LOW); // Setting LED low
        myServo.write(LOCKED_POS); // Send msg to servo to change position to locked
        break;
        
      case 1:                 // IQRF is telling arduino that door should be opened
        digitalWrite(led, HIGH); // Setting LED high
        myServo.write(OPEN_POS); // Send msg to servo to change position to open
        break;
        
      default:
        break;
    }
  }
}
