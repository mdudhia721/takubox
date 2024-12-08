#include "gamepadOutput.h"

struct DPADToHID {
    uint8_t dpadMask;
    int hatAngle;
    DPADToHID(uint8_t mask, int angle) : dpadMask(mask), hatAngle(angle){}
};

const DPADToHID DPADToHIDMaps[] = {
    DPADToHID(DPAD_STATE_MASKS[U], 0),
    DPADToHID(DPAD_STATE_MASKS[D], 180),
    DPADToHID(DPAD_STATE_MASKS[L], 270),
    DPADToHID(DPAD_STATE_MASKS[R], 90),
    DPADToHID(DPAD_STATE_MASKS[U] | DPAD_STATE_MASKS[L], 315),   //UL
    DPADToHID(DPAD_STATE_MASKS[U] | DPAD_STATE_MASKS[R], 45),  //UR
    DPADToHID(DPAD_STATE_MASKS[D] | DPAD_STATE_MASKS[L], 225),  //DL
    DPADToHID(DPAD_STATE_MASKS[D] | DPAD_STATE_MASKS[R], 135)   //DR
};

struct ButtonToHID {
    uint16_t buttonMask;
    int buttonNum;
    ButtonToHID(uint16_t mask, int n) : buttonMask(mask), buttonNum(n){}
};

const ButtonToHID ButtonToHIDMaps[] = {
    ButtonToHID(BUTTON_STATE_MASKS[A], 2),
    ButtonToHID(BUTTON_STATE_MASKS[B], 3),
    ButtonToHID(BUTTON_STATE_MASKS[X], 1),
    ButtonToHID(BUTTON_STATE_MASKS[Y], 4),
    ButtonToHID(BUTTON_STATE_MASKS[L1], 5),
    ButtonToHID(BUTTON_STATE_MASKS[R1], 6),
    ButtonToHID(BUTTON_STATE_MASKS[L2], 7),
    ButtonToHID(BUTTON_STATE_MASKS[R2], 8),
    ButtonToHID(BUTTON_STATE_MASKS[HOME], 13),
    ButtonToHID(BUTTON_STATE_MASKS[TOUCH], 14),
    ButtonToHID(BUTTON_STATE_MASKS[START], 10),
    ButtonToHID(BUTTON_STATE_MASKS[SELECT], 9),
    ButtonToHID(BUTTON_STATE_MASKS[L3], 11),
    ButtonToHID(BUTTON_STATE_MASKS[R3], 12)
};

const int HID_MIN = 0;
const int HID_ZERO = 512;
const int HID_MAX = 1023;

void GamepadOutput::outputHID(GamepadState* state) {
    //Zero out axes
    Joystick.X(HID_ZERO);            
    Joystick.Y(HID_ZERO);            
    Joystick.Z(HID_ZERO);
    Joystick.Zrotate(HID_ZERO);
    Joystick.sliderLeft(HID_ZERO);
    Joystick.sliderRight(HID_ZERO);

    outputHIDDPAD(state->dpad);
    outputHIDButtons(state->buttons);
}

void GamepadOutput::outputHIDDPAD(uint8_t dpad) {
    if(dpad == 0) {
        Joystick.hat(-1);
        return;
    }

    for(int i = 0; i < DPAD_INPUT_COUNT*2; i++) {
        if((dpad & DPADToHIDMaps[i].dpadMask) == DPADToHIDMaps[i].dpadMask) {
            Joystick.hat(DPADToHIDMaps[i].hatAngle);
        }
    }
}

void GamepadOutput::outputHIDButtons(uint16_t buttons) {
    for (int i = 0; i < BUTTON_INPUT_COUNT; i++) {
        if (buttons & ButtonToHIDMaps[i].buttonMask) {
            Joystick.button(ButtonToHIDMaps[i].buttonNum, HIGH);
        }
        else {
            Joystick.button(ButtonToHIDMaps[i].buttonNum, LOW);
        }
    }
}

void GamepadOutput::outputPadhack(GamepadState* state) {

}

/*
GAMEPAD     HID         PADHACK
A           2           X
B           3           O
X           1           □
Y           4           Δ
L1          5           L1
R1          6           R1
L2          7           L2
R2          8           R2
HOME        13          PS
TOUCH       14          TP
START       10          OPTION
SELECT      9           CREATE
L3          11          L3
R3          12          R3

U           0           
D           180
L           270
R           90
UL          315
UR          45
DL          225
DR          135
NONE        -1
*/