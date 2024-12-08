#include "gamepadDisplay.h"

void GamepadDisplay::setup() {
    screen.begin();
    screen.setFont(u8g2_font_ncenB08_tr);
}

void GamepadDisplay::displayGamepad(GamepadState *state, GamepadConfig *config) {
    screen.clearBuffer();
    displayMainButtons(state);
    displaySecondaryButtons(state);
    displayDirectionals(state, config);
    displayStatusBar(config);
    screen.sendBuffer();
}

const int MAIN_BUTTON_X0            = 72;
const int MAIN_BUTTON_Y0            = 36;
const int MAIN_BUTTON_RADIUS        = 6;
const int MAIN_BUTTON_DIAMETER      = MAIN_BUTTON_RADIUS*2;
const int MAIN_BUTTON_SPACING       = 2;
const int MAIN_BUTTON_BUMPHEIGHT    = 4; // The pixels that the 2 middle columns are "bumped" up
const Coordinate mainButtons[MAIN_INPUT_COUNT] = {
    //In order, A, B, X, Y, L1, R1, L2, R2
    Coordinate( MAIN_BUTTON_X0, 
                MAIN_BUTTON_Y0 ),
    Coordinate( MAIN_BUTTON_X0 + MAIN_BUTTON_DIAMETER + MAIN_BUTTON_SPACING, 
                MAIN_BUTTON_Y0 - MAIN_BUTTON_BUMPHEIGHT ),
    Coordinate( MAIN_BUTTON_X0,
                MAIN_BUTTON_Y0 - MAIN_BUTTON_DIAMETER - MAIN_BUTTON_SPACING ), 
    Coordinate( MAIN_BUTTON_X0 + MAIN_BUTTON_DIAMETER + MAIN_BUTTON_SPACING,
                MAIN_BUTTON_Y0 - MAIN_BUTTON_DIAMETER - MAIN_BUTTON_SPACING - MAIN_BUTTON_BUMPHEIGHT ),  
    Coordinate( MAIN_BUTTON_X0 + 3 * (MAIN_BUTTON_DIAMETER + MAIN_BUTTON_SPACING),  
                MAIN_BUTTON_Y0 - MAIN_BUTTON_DIAMETER - MAIN_BUTTON_SPACING ),                 
    Coordinate( MAIN_BUTTON_X0 + 2 * (MAIN_BUTTON_DIAMETER + MAIN_BUTTON_SPACING), 
                MAIN_BUTTON_Y0 - MAIN_BUTTON_DIAMETER - MAIN_BUTTON_SPACING - MAIN_BUTTON_BUMPHEIGHT ),
    Coordinate( MAIN_BUTTON_X0 + 3 * (MAIN_BUTTON_DIAMETER + MAIN_BUTTON_SPACING), 
                MAIN_BUTTON_Y0 ),
    Coordinate( MAIN_BUTTON_X0 + 2 * (MAIN_BUTTON_DIAMETER + MAIN_BUTTON_SPACING), 
                MAIN_BUTTON_Y0 - MAIN_BUTTON_BUMPHEIGHT )
};
void GamepadDisplay::displayMainButtons(GamepadState *state) {
    for(int i = 0; i < MAIN_INPUT_COUNT; i++) {
        screen.drawCircle(mainButtons[i].x, mainButtons[i].y, MAIN_BUTTON_RADIUS, U8G2_DRAW_ALL);
        if(state->buttons & BUTTON_STATE_MASKS[i]) {screen.drawDisc(mainButtons[i].x, mainButtons[i].y, MAIN_BUTTON_RADIUS, U8G2_DRAW_ALL);}
    }
}

const int SECONDARY_BUTTON_WIDTH    = 20;
const int SECONDARY_BUTTON_HEIGHT   = 6;
const int SECONDARY_BUTTON_X0       = 4;
const int SECONDARY_BUTTON_Y0       = -2;
const int SECONDARY_BUTTON_RADIUS   = 2;
const Coordinate secondaryButtons[SECONDARY_INPUT_COUNT] = {
    //In order Home, Touch, Start, Select, L3, R3
    Coordinate(SECONDARY_BUTTON_X0,                                 SECONDARY_BUTTON_Y0),
    Coordinate(SECONDARY_BUTTON_X0 + SECONDARY_BUTTON_WIDTH,        SECONDARY_BUTTON_Y0),
    Coordinate(SECONDARY_BUTTON_X0 + 2 * SECONDARY_BUTTON_WIDTH,    SECONDARY_BUTTON_Y0),
    Coordinate(SECONDARY_BUTTON_X0 + 3 * SECONDARY_BUTTON_WIDTH,    SECONDARY_BUTTON_Y0),
    Coordinate(SECONDARY_BUTTON_X0 + 4 * SECONDARY_BUTTON_WIDTH,    SECONDARY_BUTTON_Y0),
    Coordinate(SECONDARY_BUTTON_X0 + 5 * SECONDARY_BUTTON_WIDTH,    SECONDARY_BUTTON_Y0)
};
void GamepadDisplay::displaySecondaryButtons(GamepadState *state) {
    int j = 8; //Secondary inputs start on 8th bit of state.buttons
    for(int i = 0; i < SECONDARY_INPUT_COUNT; i++) {
        screen.drawRFrame(secondaryButtons[i].x, secondaryButtons[i].y, SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_HEIGHT, SECONDARY_BUTTON_RADIUS);
        if(state->buttons & BUTTON_STATE_MASKS[j]) {screen.drawRBox(secondaryButtons[i].x, secondaryButtons[i].y, SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_HEIGHT, SECONDARY_BUTTON_RADIUS);} 
        j++;
    }
}

void GamepadDisplay::displayDirectionals(GamepadState *state, GamepadConfig *config) {
    if (config->displayMode == DISPLAY_JOYSTICK)    { displayJoystick(state); }
    else if (config->displayMode == DISPLAY_DPAD)   { displayDPAD(state); }
    else if (config->displayMode == DISPLAY_WASD)   { displayWASD(state); }
}

const int WASD_SIZE     = 12;
const int WASD_X0       = 32;
const int WASD_Y0       = 16;
const int WASD_RADIUS   = 2;
const int WASD_SPACING  = 1;
const Coordinate wasd[DPAD_INPUT_COUNT] = {
    //In order U, D, L, R
    Coordinate(WASD_X0,                                 WASD_Y0),
    Coordinate(WASD_X0,                                 WASD_Y0 + WASD_SIZE + WASD_SPACING),
    Coordinate(WASD_X0 - WASD_SIZE - WASD_SPACING,      WASD_Y0 + WASD_SIZE + WASD_SPACING),
    Coordinate(WASD_X0 + WASD_SIZE + WASD_SPACING,      WASD_Y0 + WASD_SIZE + WASD_SPACING),
};
void GamepadDisplay::displayWASD(GamepadState *state) {
    for(int i = 0; i < DPAD_INPUT_COUNT; i++) {
            screen.drawRFrame(wasd[i].x, wasd[i].y, WASD_SIZE, WASD_SIZE, WASD_RADIUS);
            if(state->dpad & DPAD_STATE_MASKS[i]) {screen.drawRBox(wasd[i].x, wasd[i].y, WASD_SIZE, WASD_SIZE, WASD_RADIUS);}
        }
}

const int DPAD_SIZE     = 10;
const int DPAD_X0       = 32;
const int DPAD_Y0       = 14;
const int DPAD_RADIUS   = 2;
const Coordinate dpad[DPAD_INPUT_COUNT] = {
    //In order U, D, L, R
    Coordinate(DPAD_X0,             DPAD_Y0),
    Coordinate(DPAD_X0,             DPAD_Y0 + 2 * DPAD_SIZE),
    Coordinate(DPAD_X0 - DPAD_SIZE, DPAD_Y0 + DPAD_SIZE),
    Coordinate(DPAD_X0 + DPAD_SIZE, DPAD_Y0 + DPAD_SIZE)
};
void GamepadDisplay::displayDPAD(GamepadState *state) {
    for(int i = 0; i < DPAD_INPUT_COUNT; i++) {
        screen.drawRFrame(dpad[i].x, dpad[i].y, DPAD_SIZE, DPAD_SIZE, DPAD_RADIUS);
        if(state->dpad & DPAD_STATE_MASKS[i]) {screen.drawRBox(dpad[i].x, dpad[i].y, DPAD_SIZE, DPAD_SIZE, DPAD_RADIUS);}
    }
}

//TODO do hitbox at some point
void GamepadDisplay::displayHitbox(GamepadState *state) {

}

const int JOYSTICK_GATE_RADIUS  = 16;
const int JOYSTICK_RADIUS       = 8;
const int JOYSTICK_SHIFT        = 8;
const int JOYSTICK_X0           = 36;
const int JOYSTICK_Y0           = 28;
const Coordinate joystick[DPAD_INPUT_COUNT*2] = {
    //In order U, D, L, R, UL, UR, DL, DR
    Coordinate(JOYSTICK_X0,                     JOYSTICK_Y0 - JOYSTICK_SHIFT),
    Coordinate(JOYSTICK_X0,                     JOYSTICK_Y0 + JOYSTICK_SHIFT),
    Coordinate(JOYSTICK_X0 - JOYSTICK_SHIFT,    JOYSTICK_Y0),
    Coordinate(JOYSTICK_X0 + JOYSTICK_SHIFT,    JOYSTICK_Y0),
    Coordinate(JOYSTICK_X0 - JOYSTICK_SHIFT,    JOYSTICK_Y0 - JOYSTICK_SHIFT),
    Coordinate(JOYSTICK_X0 + JOYSTICK_SHIFT,    JOYSTICK_Y0 - JOYSTICK_SHIFT),
    Coordinate(JOYSTICK_X0 - JOYSTICK_SHIFT,    JOYSTICK_Y0 + JOYSTICK_SHIFT),
    Coordinate(JOYSTICK_X0 + JOYSTICK_SHIFT,    JOYSTICK_Y0 + JOYSTICK_SHIFT)
};
void GamepadDisplay::displayJoystick(GamepadState *state) {
    // Draw the joystick gate (outer circle)
    screen.drawCircle(JOYSTICK_X0, JOYSTICK_Y0, JOYSTICK_GATE_RADIUS, U8G2_DRAW_ALL);

    // Check for diagonal inputs first (in order UL, UR, DL, DR), then if no driection is pressed, then single direction
    if ((state->dpad & DPAD_STATE_MASKS[U]) && (state->dpad & DPAD_STATE_MASKS[L]))         {screen.drawDisc(joystick[4].x, joystick[4].y, JOYSTICK_RADIUS, U8G2_DRAW_ALL);}
    else if ((state->dpad & DPAD_STATE_MASKS[U]) && (state->dpad & DPAD_STATE_MASKS[R]))    {screen.drawDisc(joystick[5].x, joystick[5].y, JOYSTICK_RADIUS, U8G2_DRAW_ALL);} 
    else if ((state->dpad & DPAD_STATE_MASKS[D]) && (state->dpad & DPAD_STATE_MASKS[L]))    {screen.drawDisc(joystick[6].x, joystick[6].y, JOYSTICK_RADIUS, U8G2_DRAW_ALL);} 
    else if ((state->dpad & DPAD_STATE_MASKS[D]) && (state->dpad & DPAD_STATE_MASKS[R]))    {screen.drawDisc(joystick[7].x, joystick[7].y, JOYSTICK_RADIUS, U8G2_DRAW_ALL);} 
    else if (state->dpad == 0)                                                              {screen.drawDisc(JOYSTICK_X0, JOYSTICK_Y0, JOYSTICK_RADIUS, U8G2_DRAW_ALL);} 
    else {
        // Check for single directional inputs (U, D, L, R)
        for (int i = 0; i < DPAD_INPUT_COUNT; i++) {
            if (state->dpad & DPAD_STATE_MASKS[i]) {screen.drawDisc(joystick[i].x, joystick[i].y, JOYSTICK_RADIUS, U8G2_DRAW_ALL);}
        }
    }
}

void GamepadDisplay::displayStatusBar(GamepadConfig *config) {
    displaySOCDMode(config);
}

void GamepadDisplay::displaySOCDMode(GamepadConfig *config) {

}