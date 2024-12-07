#ifndef INPUT_DEBOUNCER_H
#define INPUT_DEBOUNCER_H

#include "gamepadConfig.h"

class InputDebouncer {
    protected:
        uint8_t debounceTime;
        uint32_t debouncedDPADTime[DPAD_INPUT_COUNT];
        uint32_t debouncedButtonTime[BUTTON_INPUT_COUNT];
        GamepadState debouncedState;

    public:
        InputDebouncer() : debounceTime(DEBOUNCE_TIME) {}
        
        void debounce(GamepadState* state) {
            uint32_t now = millis();

            //Loop thru all DPAD inputs
            for(int i = 0; i < DPAD_INPUT_COUNT; i++) {
                //Check if input has changed from previous debounced state
                if ((state->dpad & DPAD_STATE_MASKS[i]) != (debouncedState.dpad & DPAD_STATE_MASKS[i])) { 
                    // If changed, check that enough time has passed
                    if (now - debouncedDPADTime[i] >= debounceTime) { 
                        debouncedDPADTime[i] = now; //Update previous debounced input time
                        debouncedState.dpad ^= DPAD_STATE_MASKS[i]; //Accept fate, toggle bit
                    } 
                }
            }

            //Loop thru all DPAD inputs
            for(int i = 0; i < BUTTON_INPUT_COUNT; i++) {
                //Check if input has changed from previous debounced state
                if ((state->buttons & BUTTON_STATE_MASKS[i]) != (debouncedState.buttons & BUTTON_STATE_MASKS[i])) { 
                    // If changed, check that enough time has passed
                    if (now - debouncedButtonTime[i] >= debounceTime) { 
                        debouncedButtonTime[i] = now; //Update previous debounced input time
                        debouncedState.buttons ^= BUTTON_STATE_MASKS[i]; //Accept fate, toggle bit
                    } 
                }
            }

            //Update state with debounced state
            state->dpad = debouncedState.dpad;
            state->buttons = debouncedState.buttons;
        }
};

#endif