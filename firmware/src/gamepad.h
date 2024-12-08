#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "inputDebouncer.h"
#include "gamepadDisplay.h"

//Represents a mapping from Teensy input to virtual gamepad.
struct ButtonMap {
    uint8_t pin; //Input pin on teensy
    uint16_t stateMask; //Bitmask used to translate input to the GamepadState.
    
    ButtonMap(){};
    ButtonMap(uint8_t p, uint16_t m) : pin(p), stateMask(m){}
};

//Defines a "virtual" gamepad, handles all from input from humans to outputs from the pad. Other classes included within.
class Gamepad {
    protected:
        ButtonMap **dpadMaps, **buttonMaps; //Represents maps from player input to virtual gamepad
        InputDebouncer debouncer; //Used to debounce inputs
        GamepadState state; //State of virtual gamepad
        GamepadDisplay display; //Displays virtual gamepad state
        GamepadConfig config; //Configuration options for gamepad

    public:
        Gamepad(){};
        ~Gamepad(){};

        void setup(); //Setups virtual gamepad on Microcontroller
        void read(); //Reads inputs, fills state 
        void process(); //Processes state for debouncing, SOCD cleaning
        void output(); //Uses processed state to output state to system and display

        void setupConfig(); //Setups configuration options, used in setup()
        void cleanSOCD(); //Cleans SOCD, used in process()
};

#endif