#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "Arduino.h"
#include "gamepadconfig.h"
#include <MPGS.h>

struct buttonMap {
    uint8_t pin;
    const uint16_t buttonMask;

    buttonMap(uint8_t p, uint16_t bm) : pin(p), buttonMask(bm){}
};

class Gamepad : public MPGS {
    public:
    Gamepad(int debounceMS = 5, GamepadStorage *storage = &GamepadStore) : MPGS(debounceMS, storage) {}

    void setup();
    void read();
    
    buttonMap *dpadUp;
    buttonMap *dpadDown;
    buttonMap *dpadLeft;
    buttonMap *dpadRight;

    buttonMap *buttonB1;
    buttonMap *buttonB2;
    buttonMap *buttonB3;
    buttonMap *buttonB4;

    buttonMap *buttonL1;
    buttonMap *buttonR1;
    buttonMap *buttonL2;
    buttonMap *buttonR2;

    buttonMap *buttonS1;
    buttonMap *buttonS2;
    buttonMap *buttonL3;
    buttonMap *buttonR3;

    buttonMap *buttonA1;
    buttonMap *buttonA2;

    buttonMap **buttonMaps;
};

#endif