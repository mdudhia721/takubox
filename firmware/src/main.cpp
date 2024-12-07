#include "gamepad.h"

Gamepad gamepad;

void setup() {
    Serial.begin(9600);
    gamepad.setup();
}

void loop() {
    gamepad.read();
    gamepad.process();
    gamepad.output();
}