#include "gamepad.h"

uint32_t getMillis(){
    return millis(); 
}

void Gamepad::setup(){
    load();
    
    dpadUp      = new buttonMap(PIN_UP,         GAMEPAD_MASK_UP);
    dpadDown    = new buttonMap(PIN_DOWN,       GAMEPAD_MASK_DOWN);
    dpadLeft    = new buttonMap(PIN_LEFT,       GAMEPAD_MASK_LEFT);
    dpadRight   = new buttonMap(PIN_RIGHT,      GAMEPAD_MASK_RIGHT);

    buttonB1    = new buttonMap(PIN_CROSS,      GAMEPAD_MASK_B1);
    buttonB2    = new buttonMap(PIN_CIRCLE,     GAMEPAD_MASK_B2);
    buttonB3    = new buttonMap(PIN_SQUARE,     GAMEPAD_MASK_B3);
    buttonB4    = new buttonMap(PIN_TRIANGLE,   GAMEPAD_MASK_B4);

    buttonL1    = new buttonMap(PIN_L1,         GAMEPAD_MASK_L1);
    buttonR1    = new buttonMap(PIN_R1,         GAMEPAD_MASK_R1);
    buttonL2    = new buttonMap(PIN_L2,         GAMEPAD_MASK_L2);
    buttonR2    = new buttonMap(PIN_R2,         GAMEPAD_MASK_R2);

    buttonS1    = new buttonMap(PIN_SHARE,      GAMEPAD_MASK_S1);
    buttonS2    = new buttonMap(PIN_OPTIONS,    GAMEPAD_MASK_S2);
    buttonL3    = new buttonMap(PIN_L3,         GAMEPAD_MASK_L3);
    buttonR3    = new buttonMap(PIN_R3,         GAMEPAD_MASK_R3);

    buttonA1    = new buttonMap(PIN_PS,         GAMEPAD_MASK_A1);
    buttonA2    = new buttonMap(PIN_TP,         GAMEPAD_MASK_A2);

    buttonMaps = new buttonMap *[GAMEPAD_DIGITAL_INPUT_COUNT] {
        dpadUp,   dpadDown,   dpadLeft,   dpadRight,
        buttonB1,   buttonB2,   buttonB3,   buttonB4,
        buttonL1,   buttonR1,   buttonL2,   buttonR2,
        buttonS1,   buttonS2,   buttonL3,   buttonR3,
        buttonA1,   buttonA2
    };

    //Initiailize all buttons as input w/ pullup
    for(int i = 0; i < GAMEPAD_DIGITAL_INPUT_COUNT; i++){ //Change to Gamepad button ct constant, after full implementation
       pinMode(buttonMaps[i]->pin, INPUT_PULLUP);
    }

}

void Gamepad::read(){
    state.dpad = 0;
    state.buttons = 0;

    state.dpad |= digitalRead(dpadUp->pin) == LOW ? dpadUp->buttonMask : 0;
    state.dpad |= digitalRead(dpadDown->pin) == LOW ? dpadDown->buttonMask : 0;
    state.dpad |= digitalRead(dpadLeft->pin) == LOW ? dpadLeft->buttonMask : 0;
    state.dpad |= digitalRead(dpadRight->pin) == LOW ? dpadRight->buttonMask : 0;

    state.buttons |= digitalRead(buttonB1->pin) == LOW ? buttonB1->buttonMask : 0;
    state.buttons |= digitalRead(buttonB2->pin) == LOW ? buttonB2->buttonMask : 0;
    state.buttons |= digitalRead(buttonB3->pin) == LOW ? buttonB3->buttonMask : 0;
    state.buttons |= digitalRead(buttonB4->pin) == LOW ? buttonB4->buttonMask : 0;
    state.buttons |= digitalRead(buttonL1->pin) == LOW ? buttonL1->buttonMask : 0;
    state.buttons |= digitalRead(buttonR1->pin) == LOW ? buttonR1->buttonMask : 0;
    state.buttons |= digitalRead(buttonL2->pin) == LOW ? buttonL2->buttonMask : 0;
    state.buttons |= digitalRead(buttonR2->pin) == LOW ? buttonR2->buttonMask : 0;
    state.buttons |= digitalRead(buttonS1->pin) == LOW ? buttonS1->buttonMask : 0;
    state.buttons |= digitalRead(buttonS2->pin) == LOW ? buttonS2->buttonMask : 0;
    state.buttons |= digitalRead(buttonL3->pin) == LOW ? buttonL3->buttonMask : 0;
    state.buttons |= digitalRead(buttonR3->pin) == LOW ? buttonR3->buttonMask : 0;
    state.buttons |= digitalRead(buttonA1->pin) == LOW ? buttonA1->buttonMask : 0;
    state.buttons |= digitalRead(buttonA2->pin) == LOW ? buttonA2->buttonMask : 0;

	state.lx = GAMEPAD_JOYSTICK_MID;
	state.ly = GAMEPAD_JOYSTICK_MID;
	state.rx = GAMEPAD_JOYSTICK_MID;
	state.ry = GAMEPAD_JOYSTICK_MID;
	state.lt = 0;
	state.rt = 0;
}

