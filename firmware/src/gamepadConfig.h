#ifndef GAMEPADCONFIG_H
#define GAMEPADCONFIG_H

#include "gamepadState.h"

const int DEBOUNCE_TIME = 5;

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
const unsigned int PIN_L1       = 19;
const unsigned int PIN_R1       = 18;
const unsigned int PIN_L2       = 17;
const unsigned int PIN_R2       = 16;
const unsigned int PIN_START    = 15;
const unsigned int PIN_SELECT   = 14;
const unsigned int PIN_L3       = 41;
const unsigned int PIN_R3       = 40;
const unsigned int PIN_HOME     = 39;
const unsigned int PIN_TOUCH    = 38;
const unsigned int BUTTON_PINS[BUTTON_INPUT_COUNT] = {
    PIN_A,       PIN_B,       PIN_X,   PIN_Y,
    PIN_L1,      PIN_R1,      PIN_L2,  PIN_R2,
    PIN_START,   PIN_SELECT,  PIN_L3,  PIN_R3,
    PIN_HOME,    PIN_TOUCH
};

#endif