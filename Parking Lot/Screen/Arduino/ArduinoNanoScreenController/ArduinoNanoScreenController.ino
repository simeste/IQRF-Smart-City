// **************************************************************************
//   ArduinoNanoScreenController.ino - Change number based on UART input    *
// **************************************************************************
//
// Originally written by Adafruit.
// Chnegs by Simen Stensås and Kjell Kirkaune,
// for ELE3391 Elektro prosjekt in the fall of 2019 at NTNU in Gjøvik.
//
// For controlling a screen with an Arduino Nano from transciever UART input.
//
// *********************************************************************

#include <SPI.h>                // UART/SPI
#include <Wire.h>
#include <Adafruit_GFX.h>       // Library for the screen connected
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
	Serial.begin(9600);

	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
		Serial.println(F("SSD1306 allocation failed"));
		for(;;); // Don't proceed, loop forever
	}

	// Clear the buffer
	display.clearDisplay();

  drawUpdate();

	// Show the display buffer on the screen. You MUST call display() after
	// drawing commands to make them visible on screen!
	display.display();
	delay(2000);
}

void loop() {
	if(Serial.available()) // Chek for availablity of data at Serial Port
	{
		int data = Serial.read(); // Reading Serial Data and saving in data variable
    draw(data);
	}
}

void draw(int k) {
	display.clearDisplay();
  display.setTextColor(WHITE);

  // "Smart Parking Systems"
  display.setTextSize(1);
  display.setCursor(3, 0);
  display.println("Smart Parking System");

  // Number
	display.setTextSize(4);
	display.setCursor(54, 14);
	display.println(k);

   // "Open spots"
  display.setTextSize(2);
  display.setCursor(6, 48);
  display.println("Open Spots");

  // Display the above
	display.display();
	delay(2000);
}

void drawUpdate(void) {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);

  // Waiting
  display.setCursor(25, 4);
  display.println("Waiting");

  // For
  display.setCursor(50, 24);
  display.println("for");

  // Update
  display.setCursor(30, 44);
  display.println("update");

  // Display text
  display.display();
  delay(2000);
}
