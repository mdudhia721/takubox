#include "gamepad.h"

void Gamepad::setup() {
    // Map pin inputs to the gamepad state, set pins as input pullup
    Serial.println("starting setup");
    dpadMaps = new ButtonMap*[DPAD_INPUT_COUNT];
    buttonMaps = new ButtonMap*[BUTTON_INPUT_COUNT];

    // Initialize all button maps
    for (int i = 0; i < DPAD_INPUT_COUNT; i++) {
        dpadMaps[i] = new ButtonMap(DPAD_PINS[i], DPAD_STATE_MASKS[i]);
        pinMode(dpadMaps[i]->pin, INPUT_PULLUP);
    }
    for (int i = 0; i < BUTTON_INPUT_COUNT; i++) {
        buttonMaps[i] = new ButtonMap(BUTTON_PINS[i], BUTTON_STATE_MASKS[i]);
        pinMode(buttonMaps[i]->pin, INPUT_PULLUP);
    }

    loadConfig();
    display.setup();
}

void Gamepad::read() {
    // Reset inputs to 0
    state.dpad = 0;
    state.buttons = 0;

    // Read all raw inputs, update state accordingly
    for (int i = 0; i < DPAD_INPUT_COUNT; i++) {
        state.dpad |= digitalRead(dpadMaps[i]->pin) == LOW ? dpadMaps[i]->stateMask : 0;
    }
    for (int i = 0; i < BUTTON_INPUT_COUNT; i++) {
        state.buttons |= digitalRead(buttonMaps[i]->pin) == LOW ? buttonMaps[i]->stateMask : 0;
    }

    // Debounce input for stability
    debouncer.debounce(&state);
}

void Gamepad::process() {
    cleanSOCD();
}

void Gamepad::output() {
    display.displayGamepad(&state, &config);
}

void Gamepad::loadConfig() {
    // Setup default configuration
    config.socdMode = SOCD_UP;
    config.displayMode = DISPLAY_JOYSTICK;

    // Check inputs to set SOCD mode and display mode
    read();
    if (state.dpad & DPAD_STATE_MASKS[U]) {
        config.socdMode = SOCD_UP;
    } else if (state.dpad & DPAD_STATE_MASKS[D]) {
        config.socdMode = SOCD_NEUTRAL;
    } else if (state.dpad & DPAD_STATE_MASKS[L]) {
        config.socdMode = SOCD_RAW;
    }

    if (state.buttons & BUTTON_STATE_MASKS[A]) {
        config.displayMode = DISPLAY_JOYSTICK;
    } else if (state.buttons & BUTTON_STATE_MASKS[B]) {
        config.displayMode = DISPLAY_WASD;
    } else if (state.buttons & BUTTON_STATE_MASKS[X]) {
        config.displayMode = DISPLAY_DPAD;
    }
}

void Gamepad::cleanSOCD() {
    uint8_t currentDPAD = state.dpad;

    // Handle U+D filtering
    switch (config.socdMode) {
        case SOCD_NEUTRAL:
            if ((currentDPAD & DPAD_STATE_MASKS[U]) && (currentDPAD & DPAD_STATE_MASKS[D])) {
                state.dpad &= ~(DPAD_STATE_MASKS[U] | DPAD_STATE_MASKS[D]); // Clear both
            }
            break;

        case SOCD_UP:
            if ((currentDPAD & DPAD_STATE_MASKS[U]) && (currentDPAD & DPAD_STATE_MASKS[D])) {
                state.dpad &= ~DPAD_STATE_MASKS[D]; // Clear down
            }
            break;

        case SOCD_RAW:
            // Do nothing
            break;

        default:
            break;
    }

    // Handle L+R filtering
    if (config.socdMode != SOCD_RAW) {
        if ((currentDPAD & DPAD_STATE_MASKS[L]) && (currentDPAD & DPAD_STATE_MASKS[R])) {
            state.dpad &= ~(DPAD_STATE_MASKS[L] | DPAD_STATE_MASKS[R]); // Clear both
        }
    }
}