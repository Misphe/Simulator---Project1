#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <algorithm>

#define UP_ARROW 72
#define DOWN_ARROW 80
#define RIGHT_ARROW 77
#define LEFT_ARROW 75
#define ARROW_CLICK 224

#define SUPERPOWER 'f'

#define BOARD_POS_X 0 // at least 0
#define BOARD_POS_Y 3 // at least 0
#define X_SCALING 2 // blocks are placed every two coordinates instead of every one 
#define X_FRAME 2 // block the frame takes from the left
#define Y_FRAME 1 // the same sa above but y

#define HUMAN_SYMBOL 'H'
#define WOLF_SYMBOL 'W'
#define SHEEP_SYMBOL 'S'
#define FOX_SYMBOL 'F'
#define TURTLE_SYMBOL 'T'
#define ANTELOPE_SYMBOL 'A'

#define ATTACKER_WINS 1
#define DEFENDER_WINS 0
#define ATTACKER_RETREATS 2
#define DEFENDER_RUNS_AWAY 3


#define SLOW_MODE false