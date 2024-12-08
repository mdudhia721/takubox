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
        void debounce(GamepadState* state);
};

#endif