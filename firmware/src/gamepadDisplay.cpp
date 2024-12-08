#include "gamepadDisplay.h"

// Setup the display
void GamepadDisplay::setup() {
    screen.begin();
    screen.setFont(u8g2_font_sonicmania_tr);
}

// Main display function
void GamepadDisplay::displayGamepad(GamepadState *state, GamepadConfig *config) {
    screen.clearBuffer();
    displayMainButtons(state);
    displaySecondaryButtons(state);
    displayDirectionals(state, config);
    displayStatusBar(config);
    screen.sendBuffer();
}

// Main buttons configuration
const int MAIN_BUTTON_X0 = 72;
const int MAIN_BUTTON_Y0 = 36;
const int MAIN_BUTTON_RADIUS = 6;
const int MAIN_BUTTON_DIAMETER = MAIN_BUTTON_RADIUS * 2;
const int MAIN_BUTTON_SPACING = 2;
const int MAIN_BUTTON_BUMPHEIGHT = 4;

const Coordinate mainButtons[MAIN_INPUT_COUNT] = {
    Coordinate(MAIN_BUTTON_X0, MAIN_BUTTON_Y0), // A
    Coordinate(MAIN_BUTTON_X0 + MAIN_BUTTON_DIAMETER + MAIN_BUTTON_SPACING, MAIN_BUTTON_Y0 - MAIN_BUTTON_BUMPHEIGHT), // B
    Coordinate(MAIN_BUTTON_X0, MAIN_BUTTON_Y0 - MAIN_BUTTON_DIAMETER - MAIN_BUTTON_SPACING), // X
    Coordinate(MAIN_BUTTON_X0 + MAIN_BUTTON_DIAMETER + MAIN_BUTTON_SPACING, MAIN_BUTTON_Y0 - MAIN_BUTTON_DIAMETER - MAIN_BUTTON_SPACING - MAIN_BUTTON_BUMPHEIGHT), // Y
    Coordinate(MAIN_BUTTON_X0 + 3 * (MAIN_BUTTON_DIAMETER + MAIN_BUTTON_SPACING), MAIN_BUTTON_Y0 - MAIN_BUTTON_DIAMETER - MAIN_BUTTON_SPACING), // L1
    Coordinate(MAIN_BUTTON_X0 + 2 * (MAIN_BUTTON_DIAMETER + MAIN_BUTTON_SPACING), MAIN_BUTTON_Y0 - MAIN_BUTTON_DIAMETER - MAIN_BUTTON_SPACING - MAIN_BUTTON_BUMPHEIGHT), // R1
    Coordinate(MAIN_BUTTON_X0 + 3 * (MAIN_BUTTON_DIAMETER + MAIN_BUTTON_SPACING), MAIN_BUTTON_Y0), // L2
    Coordinate(MAIN_BUTTON_X0 + 2 * (MAIN_BUTTON_DIAMETER + MAIN_BUTTON_SPACING), MAIN_BUTTON_Y0 - MAIN_BUTTON_BUMPHEIGHT) // R2
};

// Display main buttons
void GamepadDisplay::displayMainButtons(GamepadState *state) {
    for (int i = 0; i < MAIN_INPUT_COUNT; i++) {
        screen.drawCircle(mainButtons[i].x, mainButtons[i].y, MAIN_BUTTON_RADIUS, U8G2_DRAW_ALL);
        if (state->buttons & BUTTON_STATE_MASKS[i]) {
            screen.drawDisc(mainButtons[i].x, mainButtons[i].y, MAIN_BUTTON_RADIUS, U8G2_DRAW_ALL);
        }
    }
}

// Secondary buttons configuration
const int SECONDARY_BUTTON_WIDTH = 20;
const int SECONDARY_BUTTON_HEIGHT = 6;
const int SECONDARY_BUTTON_X0 = 4;
const int SECONDARY_BUTTON_Y0 = -2;
const int SECONDARY_BUTTON_RADIUS = 2;

const Coordinate secondaryButtons[SECONDARY_INPUT_COUNT] = {
    Coordinate(SECONDARY_BUTTON_X0, SECONDARY_BUTTON_Y0), // Home
    Coordinate(SECONDARY_BUTTON_X0 + SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_Y0), // Touch
    Coordinate(SECONDARY_BUTTON_X0 + 2 * SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_Y0), // Start
    Coordinate(SECONDARY_BUTTON_X0 + 3 * SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_Y0), // Select
    Coordinate(SECONDARY_BUTTON_X0 + 4 * SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_Y0), // L3
    Coordinate(SECONDARY_BUTTON_X0 + 5 * SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_Y0) // R3
};

// Display secondary buttons
void GamepadDisplay::displaySecondaryButtons(GamepadState *state) {
    int j = 8; // Secondary inputs start at 8th bit of state.buttons
    for (int i = 0; i < SECONDARY_INPUT_COUNT; i++) {
        screen.drawRFrame(secondaryButtons[i].x, secondaryButtons[i].y, SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_HEIGHT, SECONDARY_BUTTON_RADIUS);
        if (state->buttons & BUTTON_STATE_MASKS[j]) {
            screen.drawRBox(secondaryButtons[i].x, secondaryButtons[i].y, SECONDARY_BUTTON_WIDTH, SECONDARY_BUTTON_HEIGHT, SECONDARY_BUTTON_RADIUS);
        }
        j++;
    }
}

// Display directional controls
void GamepadDisplay::displayDirectionals(GamepadState *state, GamepadConfig *config) {
    if (config->displayMode == DISPLAY_JOYSTICK) {
        displayJoystick(state);
    } else if (config->displayMode == DISPLAY_DPAD) {
        displayDPAD(state);
    } else if (config->displayMode == DISPLAY_WASD) {
        displayWASD(state);
    }
}

// WASD configuration
const int WASD_SIZE = 12;
const int WASD_X0 = 32;
const int WASD_Y0 = 16;
const int WASD_RADIUS = 2;
const int WASD_SPACING = 1;

const Coordinate wasd[DPAD_INPUT_COUNT] = {
    Coordinate(WASD_X0, WASD_Y0), // U
    Coordinate(WASD_X0, WASD_Y0 + WASD_SIZE + WASD_SPACING), // D
    Coordinate(WASD_X0 - WASD_SIZE - WASD_SPACING, WASD_Y0 + WASD_SIZE + WASD_SPACING), // L
    Coordinate(WASD_X0 + WASD_SIZE + WASD_SPACING, WASD_Y0 + WASD_SIZE + WASD_SPACING) // R
};

// Display WASD
void GamepadDisplay::displayWASD(GamepadState *state) {
    for (int i = 0; i < DPAD_INPUT_COUNT; i++) {
        screen.drawRFrame(wasd[i].x, wasd[i].y, WASD_SIZE, WASD_SIZE, WASD_RADIUS);
        if (state->dpad & DPAD_STATE_MASKS[i]) {
            screen.drawRBox(wasd[i].x, wasd[i].y, WASD_SIZE, WASD_SIZE, WASD_RADIUS);
        }
    }
}

// DPAD configuration
const int DPAD_SIZE = 10;
const int DPAD_X0 = 32;
const int DPAD_Y0 = 14;
const int DPAD_RADIUS = 2;

const Coordinate dpad[DPAD_INPUT_COUNT] = {
    Coordinate(DPAD_X0, DPAD_Y0), // U
    Coordinate(DPAD_X0, DPAD_Y0 + 2 * DPAD_SIZE), // D
    Coordinate(DPAD_X0 - DPAD_SIZE, DPAD_Y0 + DPAD_SIZE), // L
    Coordinate(DPAD_X0 + DPAD_SIZE, DPAD_Y0 + DPAD_SIZE) // R
};

// Display DPAD
void GamepadDisplay::displayDPAD(GamepadState *state) {
    for (int i = 0; i < DPAD_INPUT_COUNT; i++) {
        screen.drawRFrame(dpad[i].x, dpad[i].y, DPAD_SIZE, DPAD_SIZE, DPAD_RADIUS);
        if (state->dpad & DPAD_STATE_MASKS[i]) {
            screen.drawRBox(dpad[i].x, dpad[i].y, DPAD_SIZE, DPAD_SIZE, DPAD_RADIUS);
        }
    }
}

// TODO: Add hitbox display
void GamepadDisplay::displayHitbox(GamepadState *state) {
    // Future implementation
}

// Joystick configuration
const int JOYSTICK_GATE_RADIUS = 16;
const int JOYSTICK_RADIUS = 8;
const int JOYSTICK_SHIFT = 8;
const int JOYSTICK_X0 = 36;
const int JOYSTICK_Y0 = 28;

const Coordinate joystick[DPAD_INPUT_COUNT * 2] = {
    Coordinate(JOYSTICK_X0, JOYSTICK_Y0 - JOYSTICK_SHIFT), // U
    Coordinate(JOYSTICK_X0, JOYSTICK_Y0 + JOYSTICK_SHIFT), // D
    Coordinate(JOYSTICK_X0 - JOYSTICK_SHIFT, JOYSTICK_Y0), // L
    Coordinate(JOYSTICK_X0 + JOYSTICK_SHIFT, JOYSTICK_Y0), // R
    Coordinate(JOYSTICK_X0 - JOYSTICK_SHIFT, JOYSTICK_Y0 - JOYSTICK_SHIFT), // UL
    Coordinate(JOYSTICK_X0 + JOYSTICK_SHIFT, JOYSTICK_Y0 - JOYSTICK_SHIFT), // UR
    Coordinate(JOYSTICK_X0 - JOYSTICK_SHIFT, JOYSTICK_Y0 + JOYSTICK_SHIFT), // DL
    Coordinate(JOYSTICK_X0 + JOYSTICK_SHIFT, JOYSTICK_Y0 + JOYSTICK_SHIFT) // DR
};

// Display joystick
void GamepadDisplay::displayJoystick(GamepadState *state) {
    screen.drawCircle(JOYSTICK_X0, JOYSTICK_Y0, JOYSTICK_GATE_RADIUS, U8G2_DRAW_ALL);

    if ((state->dpad & DPAD_STATE_MASKS[U]) && (state->dpad & DPAD_STATE_MASKS[L])) {
        screen.drawDisc(joystick[UL].x, joystick[UL].y, JOYSTICK_RADIUS, U8G2_DRAW_ALL); // UL
    } else if ((state->dpad & DPAD_STATE_MASKS[U]) && (state->dpad & DPAD_STATE_MASKS[R])) {
        screen.drawDisc(joystick[UR].x, joystick[UR].y, JOYSTICK_RADIUS, U8G2_DRAW_ALL); // UR
    } else if ((state->dpad & DPAD_STATE_MASKS[D]) && (state->dpad & DPAD_STATE_MASKS[L])) {
        screen.drawDisc(joystick[DL].x, joystick[DL].y, JOYSTICK_RADIUS, U8G2_DRAW_ALL); // DL
    } else if ((state->dpad & DPAD_STATE_MASKS[D]) && (state->dpad & DPAD_STATE_MASKS[R])) {
        screen.drawDisc(joystick[DR].x, joystick[DR].y, JOYSTICK_RADIUS, U8G2_DRAW_ALL); // DR
    } else if (state->dpad == 0) {
        screen.drawDisc(JOYSTICK_X0, JOYSTICK_Y0, JOYSTICK_RADIUS, U8G2_DRAW_ALL); // Center
    } else {
        for (int i = 0; i < DPAD_INPUT_COUNT; i++) {
            if (state->dpad & DPAD_STATE_MASKS[i]) {
                screen.drawDisc(joystick[i].x, joystick[i].y, JOYSTICK_RADIUS, U8G2_DRAW_ALL);
            }
        }
    }
}

// Status bar configuration
const int SOCD_X0 = 4;
const int SOCD_Y0 = 64;

// Display SOCD mode
void GamepadDisplay::displaySOCDMode(GamepadConfig *config) {
    if (config->socdMode == SOCD_NEUTRAL) {
        screen.drawStr(SOCD_X0, SOCD_Y0, "U+D=N");
    } else if (config->socdMode == SOCD_UP) {
        screen.drawStr(SOCD_X0, SOCD_Y0, "U+D=U");
    } else if (config->socdMode == SOCD_RAW) {
        screen.drawStr(SOCD_X0, SOCD_Y0, "RAW");
    }
}

// Display status bar
void GamepadDisplay::displayStatusBar(GamepadConfig *config) {
    displaySOCDMode(config);
}