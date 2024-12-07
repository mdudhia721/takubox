#include "gamepad.h"

void Gamepad::setup() {
    // Map pin inputs to the gamepad state, set pins as input pullup
    Serial.println("starting setup");
    dpadMaps = new ButtonMap*[DPAD_INPUT_COUNT];
    buttonMaps = new ButtonMap*[BUTTON_INPUT_COUNT];

    //Initialize all button maps
    for(int i = 0; i < DPAD_INPUT_COUNT; i++) {
        dpadMaps[i] = new ButtonMap(DPAD_PINS[i], DPAD_STATE_MASKS[i]);
        pinMode(dpadMaps[i]->pin, INPUT_PULLUP);
    }
    for(int i = 0; i < BUTTON_INPUT_COUNT; i++) {
        buttonMaps[i] = new ButtonMap(BUTTON_PINS[i], BUTTON_STATE_MASKS[i]);
        pinMode(buttonMaps[i]->pin, INPUT_PULLUP);
    }

}

void Gamepad::read() {
    //Reset inputs to 0
    state.dpad = 0;
    state.buttons = 0;

    //Read all raw inputs, update state accordingly
    for(int i = 0; i < DPAD_INPUT_COUNT; i++) { state.dpad |= digitalRead(dpadMaps[i]->pin) == LOW ? dpadMaps[i]->stateMask : 0; }
    for(int i = 0; i < BUTTON_INPUT_COUNT; i++) { state.buttons |= digitalRead(buttonMaps[i]->pin) == LOW ? buttonMaps[i]->stateMask : 0; }

    //Debounce input for stability
    debouncer.debounce(&state);
}

void Gamepad::process() {

}

void Gamepad::output() {
    
}