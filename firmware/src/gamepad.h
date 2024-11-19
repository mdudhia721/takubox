#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "gamepadSetup.h"

//Defines a "virtual" gamepad, handles all from input from humans to outputs from the pad
class Gamepad{
    protected:
        ButtonMap** buttonMaps; //Represents maps from player input to virtual gamepad
        GamepadState state; //State of virtual gamepad

    public:
        Gamepad();
        ~Gamepad();

        void setup(); //Setups virtual gamepad on Teensy
        void read(); //Reads inputs, fills state 
        void process(); //Processes state for debouncing, SOCD cleaning
        void output(); //Uses processed state to output state to system
};


#endif