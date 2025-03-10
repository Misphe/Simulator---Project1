#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <string>
#include <fstream>
#include <stdexcept>

#define UP_ARROW 72
#define DOWN_ARROW 80
#define RIGHT_ARROW 77
#define LEFT_ARROW 75
#define ARROW_CLICK 224
#define ESCAPE 27

#define SUPERPOWER 'f'
#define SAVE 's'
#define LOAD 'l'
#define REFRESH 'r'

#define BOARD_POS_X 0 // at least 0
#define BOARD_POS_Y 0 // at least 0
#define X_SCALING 2   // blocks are placed every two coordinates instead of every one 
#define X_FRAME 2     // block the frame takes from the left
#define Y_FRAME 1     // the same sa above but y

#define LOG_X (BOARD_POS_X + size_x * X_SCALING + X_FRAME + 10)
#define LOG_Y (BOARD_POS_Y)
#define LOG_LENGTH 20
#define LOG_LINE_LENGTH 50

#define HUMAN_SYMBOL 'H'
#define WOLF_SYMBOL 'W'
#define SHEEP_SYMBOL 'S'
#define FOX_SYMBOL 'F'
#define TURTLE_SYMBOL 'T'
#define ANTELOPE_SYMBOL 'A'

#define GRASS_SYMBOL 'G'
#define DANDELION_SYMBOL 'D'
#define GUARANA_SYMBOL 'U'
#define WOLFBERRIES_SYMBOL 'B'
#define PINEBORSCHT_SYMBOL 'P'

#define ATTACKER_WINS 1
#define DEFENDER_WINS 0
#define ATTACKER_RETREATS 2
#define DEFENDER_RUNS_AWAY 3
#define BOTH_DIED 4
#define ATTACKER_EATS 5

#define NO_EMPTY_ADJACENT -1

#define SLOW_MODE false
#define DEBUG_MODE false

#define RESET_COLOR std::cout<<"\033[0m"
#define SET_LETTER_RED std::cout<<"\033[31m"
#define SET_LETTER_GREEN std::cout<<"\033[32m"
#define SET_LETTER_YELLOW std::cout<<"\033[33m"
#define SET_LETTER_BLUE std::cout<<"\033[34m"
#define SET_LETTER_MAGENTA std::cout<<"\033[35m"
#define SET_LETTER_CYAN std::cout<<"\033[36m"
#define SET_LETTER_WHITE std::cout<<"\033[37m"
#define SET_LETTER_BLACK std::cout<<"\033[30m"

#define SET_BG_BLACK 0 
#define SET_BG_BLUE 16
#define SET_BG_GREEN 32			 // Human
#define SET_BG_CYAN 48			 // Turtle
#define SET_BG_RED 64			 // Fox
#define SET_BG_MAGENTA 80		 // Guarana
#define SET_BG_YELLOW 96		 // Dandelion
#define SET_BG_GRAY 112			 // Wolf
#define SET_BG_DARKGRAY 128		 // Wolf Berries
#define SET_BG_LIGHTBLUE 144	 // Map border
#define SET_BG_LIGHTGREEN 160	 // Grass
#define SET_BG_LIGHTCYAN 176
#define SET_BG_LIGHTRED 192		 // Pine Borscht
#define SET_BG_LIGHTMAGENTA 208  // Antelope
#define SET_BG_LIGHTYELLOW 224	 // Map surface
#define SET_BG_WHITE 240		 // Sheep

#define HUMAN_COLOR			SET_BG_GREEN 
#define TURTLE_COLOR		SET_BG_CYAN 
#define FOX_COLOR			SET_BG_RED
#define GUARANA_COLOR		SET_BG_MAGENTA
#define DANDELION_COLOR		SET_BG_YELLOW
#define WOLF_COLOR			SET_BG_GRAY
#define WOLFBERRIES_COLOR   SET_BG_DARKGRAY
#define MAP_BORDER_COLOR	SET_BG_LIGHTBLUE
#define GRASS_COLOR			SET_BG_LIGHTGREEN
#define PINEBORSCHT_COLOR	SET_BG_LIGHTRED
#define ANTELOPE_COLOR		SET_BG_LIGHTMAGENTA
#define MAP_SURFACE_COLOR	SET_BG_LIGHTYELLOW
#define SHEEP_COLOR			SET_BG_WHITE

#define PLANT_STRENGTH 0
#define PLANT_SPREAD_CHANCE 20 // one in (this number) chance
#define GUARANA_BOOST 3

#define HUMAN_STRENGTH 5
#define HUMAN_INITIATIVE 4
#define MAX_COOLDOWN 10
#define END_OF_POWER 5
#define POWER_WORSE_STATE 7

#define WOLF_STRENGTH 9 
#define WOLF_INITIATIVE 5

#define SHEEP_STRENGTH 4 
#define SHEEP_INITIATIVE 4

#define FOX_STRENGTH 3
#define FOX_INITIATIVE 7

#define TURTLE_STRENGTH 2
#define TURTLE_INITIATIVE 1
#define MIN_ATTACK_TO_KILL 4 
#define TURTLE_MOVE_CHANCE 4 // one in (this number) chance

#define ANTELOPE_STRENGTH 4
#define ANTELOPE_INITIATIVE 4
#define ANTELOPE_JUMP 2

#define WOLFBERRIES_STRENGTH 99

#define PINEBORSCHT_STRENGTH 10

#define DANDELION_TURNS 3

#define WOLF_COUNT 4
#define SHEEP_COUNT 4
#define FOX_COUNT 4
#define TURTLE_COUNT 4
#define ANTELOPE_COUNT 4
#define GRASS_COUNT 4
#define DANDELION_COUNT 4
#define GUARANA_COUNT 4
#define WOLFBERRIES_COUNT 4
#define PINEBORSCHT_COUNT 4

#define ORGANISMS_COUNT \
    ( \
        WOLF_COUNT + \
        SHEEP_COUNT + \
        FOX_COUNT + \
        TURTLE_COUNT + \
        ANTELOPE_COUNT + \
        GRASS_COUNT + \
        DANDELION_COUNT + \
        GUARANA_COUNT + \
        WOLFBERRIES_COUNT + \
        PINEBORSCHT_COUNT + \
        1 \
    )

#define UNIQUE_ORGANISMS 11
#define MIN_MAP_SIZE 8

#define LEGEND_X	LOG_X
#define LEGEND_Y	(LOG_Y + LOG_LENGTH + 2)

#define CONTROLS_X	LEGEND_X + 20
#define CONTROLS_Y	LEGEND_Y

#define NOT_IN_PLAY -1