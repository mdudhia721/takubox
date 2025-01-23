#ifndef GAMEPADDISPLAY_H
#define GAMEPADDISPLAY_H

#include "gamepadConfig.h"
#include <U8g2lib.h>

struct Coordinate {
    int x, y;
    Coordinate() : x(0), y(0) {}
    Coordinate(int x, int y) : x(x), y(y) {}
};

class GamepadDisplay {
    protected:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C screen;
    GamepadConfig config;
    
    public:
        GamepadDisplay() : screen(U8G2_R0, U8X8_PIN_NONE){}
        
        void setup();

        //TODO: Low priority, change methods so they only rely on their correspdoning part of state, not all of state. Directionals only uses dpad, buttons only uses buttons, etc. 
        void displayGamepad(GamepadState *state, GamepadConfig *config);
        void displayMainButtons(GamepadState *state);
        void displaySecondaryButtons(GamepadState *state);
        void displayDirectionals(GamepadState *state, GamepadConfig *config);

        void displayWASD(GamepadState *state);
        void displayDPAD(GamepadState *state);
        void displayHitbox(GamepadState *state); //Todo need to implement
        void displayJoystick(GamepadState *state);

        void displayStatusBar(GamepadConfig *config);
        void displaySOCDMode(GamepadConfig *config);
        void displayOutputMode(GamepadConfig *config);
};

#endif