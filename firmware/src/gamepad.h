#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "gamepadConfig.h"
#include "inputDebouncer.h"

//Represents a mapping from Teensy input to virtual gamepad.
struct ButtonMap {
    uint8_t pin; //Input pin on teensy
    uint16_t stateMask; //Bitmask used to translate input to the GamepadState.
    
    ButtonMap(){};
    ButtonMap(uint8_t p, uint16_t m) : pin(p), stateMask(m){}
};

//Defines a "virtual" gamepad, handles all from input from humans to outputs from the pad
class Gamepad {
    protected:
        ButtonMap **dpadMaps, **buttonMaps; //Represents maps from player input to virtual gamepad
        InputDebouncer debouncer; //Used to debounce inputs
        GamepadState state; //State of virtual gamepad

    public:
        Gamepad(){};
        ~Gamepad(){};

        void setup(); //Setups virtual gamepad on Teensy
        void read(); //Reads inputs, fills state 
        void process(); //Processes state for debouncing, SOCD cleaning
        void output(); //Uses processed state to output state to system
};

#endif