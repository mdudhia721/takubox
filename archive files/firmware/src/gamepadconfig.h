#ifndef GAMEPADCONFIG_H
#define GAMEPADCONFIG_H

//Physical pins for Gamepad buttons
#define PIN_UP          19
#define PIN_DOWN        18
#define PIN_LEFT        17
#define PIN_RIGHT       16

#define PIN_CROSS       6
#define PIN_CIRCLE      7
#define PIN_SQUARE      0
#define PIN_TRIANGLE    1

#define PIN_L1          3
#define PIN_R1          2
#define PIN_L2          9
#define PIN_R2          8

#define PIN_SHARE       20
#define PIN_OPTIONS     21
#define PIN_L3          22
#define PIN_R3          26

#define PIN_PS          27
#define PIN_TP          28

//For padhack output
#define PIN_UPOUT       12
#define PIN_DOWNOUT     13
#define PIN_LEFTOUT     14
#define PIN_RIGHTOUT    15

/*
    +--------+--------+---------+----------+----------+--------+
	| MPG    | XInput | Switch  | PS3      | DInput   | Arcade |
	+--------+--------+---------+----------|----------+--------+
	| B1     | A      | B       | Cross    | 2        | K1     |
	| B2     | B      | A       | Circle   | 3        | K2     |
	| B3     | X      | Y       | Square   | 1        | P1     |
	| B4     | Y      | X       | Triangle | 4        | P2     |
	| L1     | LB     | L       | L1       | 5        | P4     |
	| R1     | RB     | R       | R1       | 6        | P3     |
	| L2     | LT     | ZL      | L2       | 7        | K4     |
	| R2     | RT     | ZR      | R2       | 8        | K3     |
	| S1     | Back   | -       | Select   | 9        | Coin   |
	| S2     | Start  | +       | Start    | 10       | Start  |
	| L3     | LS     | LS      | L3       | 11       | LS     |
	| R3     | RS     | RS      | R3       | 12       | RS     |
	| A1     | Guide  | Home    | -        | 13       | -      |
	| A2     | -      | Capture | -        | 14       | -      |
	+--------+--------+---------+----------+----------+--------+
*/

#endif