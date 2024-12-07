#ifndef GAMEPADSTATE_H
#define GAMEPADSTATE_H

//Sets up objects and constants needed for Gamepad class.
#include <Arduino.h>

// Input count constants
const int DPAD_INPUT_COUNT = 4;
const int BUTTON_INPUT_COUNT = 14;
const int TOTAL_INPUT_COUNT = DPAD_INPUT_COUNT + BUTTON_INPUT_COUNT;

// State mask constats for Dpad
const uint8_t STATE_MASK_U = (1 << 0);
const uint8_t STATE_MASK_D = (1 << 1);
const uint8_t STATE_MASK_L = (1 << 2);
const uint8_t STATE_MASK_R = (1 << 3);
const uint8_t DPAD_STATE_MASKS[DPAD_INPUT_COUNT] = { 
    STATE_MASK_U, 
    STATE_MASK_D, 
    STATE_MASK_L, 
    STATE_MASK_R
};

const uint16_t STATE_MASK_A =        (1 << 0);
const uint16_t STATE_MASK_B =        (1 << 1);
const uint16_t STATE_MASK_X =        (1 << 2);
const uint16_t STATE_MASK_Y =        (1 << 3);
const uint16_t STATE_MASK_L1 =       (1 << 4);
const uint16_t STATE_MASK_R1 =       (1 << 5);
const uint16_t STATE_MASK_L2 =       (1 << 6);
const uint16_t STATE_MASK_R2 =       (1 << 7);
const uint16_t STATE_MASK_START =    (1 << 8);
const uint16_t STATE_MASK_SELECT =   (1 << 9);
const uint16_t STATE_MASK_L3 =       (1 << 10);
const uint16_t STATE_MASK_R3 =       (1 << 11);
const uint16_t STATE_MASK_HOME =     (1 << 12);
const uint16_t STATE_MASK_TOUCH =    (1 << 13);
const uint16_t BUTTON_STATE_MASKS[BUTTON_INPUT_COUNT] = {
    STATE_MASK_A,       STATE_MASK_B,       STATE_MASK_X,   STATE_MASK_Y,
    STATE_MASK_L1,      STATE_MASK_R1,      STATE_MASK_L2,  STATE_MASK_R2,
    STATE_MASK_START,   STATE_MASK_SELECT,  STATE_MASK_L3,  STATE_MASK_R3,
    STATE_MASK_HOME,    STATE_MASK_TOUCH
};

// Analog range constatns
const uint16_t ANALOG_MIN = 0;
const uint16_t ANALOG_ZERO = 0x7FFF;
const uint16_t ANALOG_MAX = 0xFFFF;

//Represents the state of the virtual gamepad
struct GamepadState {
    uint16_t buttons {0};
    uint8_t dpad {0};
	uint16_t lx {ANALOG_ZERO};
	uint16_t ly {ANALOG_ZERO};
	uint16_t rx {ANALOG_ZERO};
	uint16_t ry {ANALOG_ZERO};
	uint8_t lt {0};
	uint8_t rt {0};
};

#endif