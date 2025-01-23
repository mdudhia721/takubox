#include "gamepad.h"

Gamepad gamepad;

void setup() {
    gamepad.setup();
}

void loop() {
    gamepad.read();
    gamepad.process();
    gamepad.output();
}