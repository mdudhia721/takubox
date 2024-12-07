/*#ifndef GAMEPADDISPLAY_H
#define GAMEPADDISPLAY_H

#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE); //U8G2_SSD1306_96X40_F_HW_I2C(rotation, [reset [, clock, data]]) [full framebuffer, size = 480 bytes]

// Display WASD properties
#define WASDSTARTX          12;
#define WASDSTARTY          24;
#define WASDBUTTONSIZE      12;
#define WASDCORNERRADIUS    2;
#define WASDSPACING         1;

// WASD X Coordinates
int wasdX[4] = {WASDSTARTX + WASDBUTTONSIZE + WASDSPACING,          // U
                WASDSTARTX + WASDBUTTONSIZE + WASDSPACING,          // D
                WASDSTARTX,                                         // L
                WASDSTARTX + (2*WASDBUTTONSIZE) + (2*WASDSPACING)}; // R

int wasdY[4] = {WASDSTARTY,                                         // U
                WASDSTARTY + WASDBUTTONSIZE + WASDSPACING,          // D
                WASDSTARTY + WASDBUTTONSIZE + WASDSPACING,          // L
                WASDSTARTY + WASDBUTTONSIZE + WASDSPACING};         // R

// Display Button properties
#define BUTTONSTARTX        68
#define BUTTONSTARTY        30
#define BUTTONRADIUS        6
#define BUTTONDIAMETER      BUTTONRADIUS*2
#define BUTTONSPACING       2
#define BUTTONBUMPHEIGHT    4 // The pixels that the 2 middle columns are "bumped" up

// Button X and Y positions
int buttonX[8] = {BUTTONSTARTX,                                                     // Square
                BUTTONSTARTX + BUTTONDIAMETER + BUTTONSPACING,                      // Triangle
                BUTTONSTARTX + (2*BUTTONDIAMETER) + (2*BUTTONSPACING),              // R1
                BUTTONSTARTX + (3*BUTTONDIAMETER) + (3*BUTTONSPACING),              // L1
                BUTTONSTARTX,                                                       // Cross
                BUTTONSTARTX + BUTTONDIAMETER + BUTTONSPACING,                      // Circle
                BUTTONSTARTX + (2*BUTTONDIAMETER) + (2*BUTTONSPACING),              // R2
                BUTTONSTARTX + (3*BUTTONDIAMETER) + (3*BUTTONSPACING)};             // L2

int buttonY[8] = {BUTTONSTARTY,                                                     // Square
                BUTTONSTARTY - BUTTONBUMPHEIGHT,                                    // Triangle
                BUTTONSTARTY - BUTTONBUMPHEIGHT,                                    // R1
                BUTTONSTARTY,                                                       // L1
                BUTTONSTARTY + BUTTONDIAMETER + BUTTONSPACING,                      // Cross
                BUTTONSTARTY + BUTTONDIAMETER + BUTTONSPACING - BUTTONBUMPHEIGHT,   // Circle 
                BUTTONSTARTY + BUTTONDIAMETER + BUTTONSPACING - BUTTONBUMPHEIGHT,   // R2
                BUTTONSTARTY + BUTTONDIAMETER + BUTTONSPACING};                     // L2

void displayGamepad(){
    displayStatusBar();
    //WASD
    for(int i = 0; i < 4; i++){
        display.drawRFrame(wasdX[i], wasdY[i], wasdButtonSize, wasdButtonSize, wasdCornerRadius);
    }
    //Buttons
    for(int i = 0; i < 8; i++){
        display.drawCircle(buttonX[i], buttonY[i], BUTTONDIAMETER, U8G2_DRAW_ALL);
    }
}

void displayStatusBar(){
    switch (socdMode){
        case 1:
            display.drawStr(0,12,"SOCD: U");
            break;
        case 2: 
            display.drawStr(0,12,"SOCD: N");
            break;
        case 3:
            display.drawStr(0,12,"SOCD: R");
            break;
        default:
            break;
    }
}
void displayInputs(bool* dpadStates, bool* buttonStates){
    //WASD inputs
    for(int i = 0; i < 4; i++){
        if(dpadStates[i]){
            display.drawRBox(wasdX[i], wasdY[i], wasdButtonSize, wasdButtonSize, wasdCornerRadius);
        }
    }

    //Button inputs
    for(int i = 0; i < 8; i++){
        if(buttonStates[i]){
            display.drawDisc(buttonX[i], buttonY[i], buttonRadius, U8G2_DRAW_ALL);
        }
    }
}

#endif*/