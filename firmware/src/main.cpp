#include "Arduino.h"
#include <Wire.h>
#include <U8g2lib.h>
#include <Adafruit_TinyUSB.h>

#include "ButtonConfig.h"
#include "DisplayConfig.h"

//DPAD button variables
bool upRaw, downRaw, leftRaw, rightRaw;
bool upFiltered, downFiltered, leftFiltered, rightFiltered;

//Other buttons
bool square, triangle, r1, l1, cross, circle, r2, l2;

//Mode selects
int socdMode, gamepadMode;

//Display
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE); //U8G2_SSD1306_96X40_F_HW_I2C(rotation, [reset [, clock, data]]) [full framebuffer, size = 480 bytes]

void socdOutputXInput();

void socdOutput(); // Filtered SOCD output
void socdStandard(); // L+R = N | U+D = U
void socdAlternative(); // L+R = N | U+D = N
void socdRaw(); // Raw inputs

void displayGamepad();
void displayStatusBar();
void displayInputs(bool*, bool*);

void setup() {
    //Initialize DPAD inputs and outputs
    pinMode(UPIN, INPUT_PULLUP);
    pinMode(DOWNIN, INPUT_PULLUP);
    pinMode(LEFTIN, INPUT_PULLUP);
    pinMode(RIGHTIN, INPUT_PULLUP);

    pinMode(UPOUT, INPUT);
    pinMode(DOWNOUT, INPUT);
    pinMode(LEFTOUT, INPUT);
    pinMode(RIGHTOUT, INPUT);

    //Initialize filtered SOCD output
    upFiltered = downFiltered = leftFiltered = rightFiltered = false;

    //Initialize Button inputs
    pinMode(SQUAREIN, INPUT);
    pinMode(TRIANGLEIN, INPUT);
    pinMode(R1IN, INPUT);
    pinMode(L1IN, INPUT);

    pinMode(CROSSIN, INPUT);
    pinMode(CIRCLEIN, INPUT);
    pinMode(R2IN, INPUT);
    pinMode(L2IN, INPUT);
    
    //Initialize I2C and display
    Wire.begin();
    display.begin();
    display.setFont(u8g2_font_sonicmania_tr);

    //Read Up and Down inputs for SOCD select
    upRaw = !digitalRead(UPIN);
    downRaw = !digitalRead(DOWNIN);

    //Initialize SOCD mode
    if(upRaw && !downRaw){
        socdMode = 1; //If up on startup, standard SOCD
    }
    else if(!upRaw && downRaw){
        socdMode = 2; //If down on startup, alternative SOCD
    }
    else if(upRaw && downRaw){
        socdMode = 3; //If up & down on startup, raw outputs
    }
    else{
        socdMode = 1; //Standard SOCD by default
    }

    //Initialize Gamepad mode
    gamepadMode = 0;
    if(gamepadMode == 0){
    }
}
void loop() {
    display.clearBuffer();

    //Read DPAD inputs
    upRaw = !digitalRead(UPIN);
    downRaw = !digitalRead(DOWNIN);
    leftRaw = !digitalRead(LEFTIN);
    rightRaw = !digitalRead(RIGHTIN);
    bool dpadStates[4] = {upFiltered, downFiltered, leftFiltered, rightFiltered};

    //Read Button Inputs
    square = !digitalRead(SQUAREIN);
    triangle = !digitalRead(TRIANGLEIN);
    r1 = !digitalRead(R1IN);
    l1 = !digitalRead(L1IN);
    cross = !digitalRead(CROSSIN);
    circle = !digitalRead(CIRCLEIN);
    r2 = !digitalRead(R2IN);
    l2 = !digitalRead(L2IN);
    bool buttonStates[8] = {square, triangle, r1, l1, cross, circle, r2, l2};
    
    //Filter DPAD inputs based on SOCD mode
    switch (socdMode){
        case 1:
            socdStandard();
            break;
        case 2:
            socdAlternative();
            break;
        case 3:
            socdRaw();
            break;
        default:
            break;
    }
    
    if(gamepadMode == 0){
        //socdOutputXInput();
    }
    socdOutput();

    //Update Display
    displayGamepad();
    displayInputs(dpadStates, buttonStates);
    display.sendBuffer();
}

void socdOutput(){
    pinMode(UPOUT, upFiltered ? OUTPUT : INPUT);
    digitalWrite(UPOUT, upFiltered ? LOW : HIGH);
    
    pinMode(DOWNOUT, downFiltered ? OUTPUT : INPUT);
    digitalWrite(DOWNOUT, downFiltered ? LOW : HIGH);
    
    pinMode(LEFTOUT, leftFiltered ? OUTPUT : INPUT);
    digitalWrite(LEFTOUT, leftFiltered ? LOW : HIGH);
    
    pinMode(RIGHTOUT, rightFiltered ? OUTPUT : INPUT);
    digitalWrite(RIGHTOUT, rightFiltered ? LOW : HIGH);
}
void socdStandard(){
    //L+R = N
    leftFiltered = leftRaw && !rightRaw;
    rightFiltered = rightRaw && !leftRaw;
    //U+D = U
    upFiltered = upRaw;
    downFiltered = downRaw && !upRaw && !upFiltered;
}
void socdAlternative(){
    //L+R = N
    leftFiltered = leftRaw && !rightRaw;
    rightFiltered = rightRaw && !leftRaw;
    //U+D = N
    upFiltered = upRaw && !downRaw;
    downFiltered = downRaw && !upRaw;
}
void socdRaw(){
    upFiltered = upRaw;
    downFiltered = downRaw;
    leftFiltered = leftRaw;
    rightFiltered = rightRaw;
}

void displayGamepad(){
displayStatusBar();
    //WASD
    for(int i = 0; i < 4; i++){
        display.drawRFrame(wasdX[i], wasdY[i], wasdButtonSize, wasdButtonSize, wasdCornerRadius);
    }

    //Buttons
    for(int i = 0; i < 8; i++){
        display.drawCircle(buttonX[i], buttonY[i], buttonRadius, U8G2_DRAW_ALL);
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