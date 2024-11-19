#ifndef GAMEPADSETUP_H
#define GAMEPADSETUP_H

//Sets up objects and constants needed for Gamepad class.
#include <Arduino.h>

#define ANALOG_MIN 0
#define ANALOG_MID 0x7FFF
#define ANALOG_MAX 0xFFFF

//Represents a mapping from Teensy input to virtual gamepad.
struct ButtonMap {
    uint8_t pin; //Input pin on teensy
    const uint16_t stateMask; //Bitmask used to translate input to the GamepadState.
    
    ButtonMap (uint8_t p, uint16_t m) : pin(p), stateMask(m){}
};

//Represents the state of the virtual gamepad
struct GamepadState {
    uint16_t buttons {0};
    uint8_t dpad {0};
	uint16_t lx {ANALOG_MID};
	uint16_t ly {ANALOG_MID};
	uint16_t rx {ANALOG_MID};
	uint16_t ry {ANALOG_MID};
	uint8_t lt {0};
	uint8_t rt {0};
};



#endif