#ifndef GAMEPADCONFIG_H
#define GAMEPADCONFIG_H

#include "gamepadState.h"

const int DEBOUNCE_TIME = 5;

const unsigned int PIN_RESET = 33;

//TODO make pins into ports
const unsigned int PIN_U = 34;
const unsigned int PIN_D = 35;
const unsigned int PIN_L = 36;
const unsigned int PIN_R = 37;
const unsigned int DPAD_PINS[DPAD_INPUT_COUNT] = {
    PIN_U, PIN_D, PIN_L, PIN_R
};

const unsigned int PIN_A        = 23;
const unsigned int PIN_B        = 22;
const unsigned int PIN_X        = 21;
const unsigned int PIN_Y        = 20;
const unsigned int PIN_L1       = 24;
const unsigned int PIN_R1       = 25;
const unsigned int PIN_L2       = 17;
const unsigned int PIN_R2       = 16;
const unsigned int PIN_HOME     = 15;
const unsigned int PIN_TOUCH    = 14;
const unsigned int PIN_START    = 41;
const unsigned int PIN_SELECT   = 40;
const unsigned int PIN_L3       = 39;
const unsigned int PIN_R3       = 38;
const unsigned int BUTTON_PINS[BUTTON_INPUT_COUNT] = {
    PIN_A,      PIN_B,       PIN_X,     PIN_Y,
    PIN_L1,     PIN_R1,      PIN_L2,    PIN_R2,
    PIN_HOME,   PIN_TOUCH,   PIN_START, PIN_SELECT,
    PIN_L3,     PIN_R3
};

const unsigned int L3_OUT = 27;
const unsigned int R3_OUT = 28;

enum socdMode {
    SOCD_UP,
    SOCD_NEUTRAL,
    SOCD_RAW
};

enum displayMode {
    DISPLAY_JOYSTICK,
    DISPLAY_DPAD,
    DISPLAY_WASD
};

enum outputMode {
    OUTPUT_HID,
    OUTPUT_PADHACK
};

struct GamepadConfig {
    uint8_t socdMode;
    uint8_t displayMode;
    uint8_t outputMode;
    
    GamepadConfig() : socdMode(SOCD_UP), displayMode(DISPLAY_JOYSTICK), outputMode(OUTPUT_HID) {}
};

#endif