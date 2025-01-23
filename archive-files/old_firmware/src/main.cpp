#define GAMEPAD_DEBOUNCE_MILLIS 5

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_TinyUSB.h>
#include "Gamepad.h"

Gamepad gamepad(GAMEPAD_DEBOUNCE_MILLIS);

void setup() {
    Serial.begin(115200);

    gamepad.setup();
    gamepad.read();
}

void loop() {
    static void *report;
    static const uint8_t reportSize = gamepad.getReportSize();  // Get report size from Gamepad instance                      

	gamepad.read();                                             // Read raw inputs
	gamepad.debounce();                                         // Run debouncing if enabled                                 
	gamepad.process();                                          // Perform final input processing (SOCD cleaning, LS/RS emulation, etc.)
}