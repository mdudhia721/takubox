#ifndef GAMEPADOUTPUT_H
#define GAMEPADOUTPUT_H

#include "gamepadConfig.h"

class GamepadOutput {
    public:
    void outputHID(GamepadState* state);
    void outputHIDDPAD(uint8_t dpad);
    void outputHIDButtons(uint16_t buttons);
    void outputPadhack(GamepadState* state);
};

#endif