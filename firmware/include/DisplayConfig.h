#ifndef DISPLAYCONFIG_H
#define DISPLAYCONFIG_H

// Display WASD properties
int wasdStartX = 12;
int wasdStartY = 24;
int wasdButtonSize = 12;
int wasdCornerRadius = 2;
int wasdSpacing = 1;

// U, D, L, R
int wasdX[4] = {wasdStartX + wasdButtonSize + wasdSpacing, wasdStartX + wasdButtonSize + wasdSpacing, wasdStartX, wasdStartX + (2*wasdButtonSize) + (2*wasdSpacing)};
int wasdY[4] = {wasdStartY, wasdStartY + wasdButtonSize + wasdSpacing, wasdStartY + wasdButtonSize + wasdSpacing, wasdStartY + wasdButtonSize + wasdSpacing};

// Display Button properties
int buttonStartX = 68;
int buttonStartY = 30;
int buttonRadius = 6;
int buttonDiameter = buttonRadius*2;
int buttonSpacing = 2;
int buttonBumpHeight = 4; // The pixels that the 2 middle columns are "bumped" up

// Button X and Y positions
int buttonX[8] = {buttonStartX, buttonStartX + buttonDiameter + buttonSpacing, buttonStartX + (2*buttonDiameter) + (2*buttonSpacing), buttonStartX + (3*buttonDiameter) + (3*buttonSpacing),
                  buttonStartX, buttonStartX + buttonDiameter + buttonSpacing, buttonStartX + (2*buttonDiameter) + (2*buttonSpacing), buttonStartX + (3*buttonDiameter) + (3*buttonSpacing)};

int buttonY[8] = {buttonStartY, buttonStartY - buttonBumpHeight, buttonStartY - buttonBumpHeight, buttonStartY,
                  buttonStartY + buttonDiameter + buttonSpacing, buttonStartY + buttonDiameter + buttonSpacing - buttonBumpHeight, buttonStartY + buttonDiameter + buttonSpacing - buttonBumpHeight, buttonStartY + buttonDiameter + buttonSpacing};

#endif