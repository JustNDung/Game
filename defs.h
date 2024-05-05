#ifndef _DEFS__H
#define _DEFS__H
#include "graphics.h"

#define N 20
#define WINDOW_WIDTH  900
#define WINDOW_HEIGHT  900
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT  800
#define INITIAL_SNAKE_X  10
#define INITIAL_SNAKE_Y  10
#define INITIAL_GRID_X 50
#define INITIAL_GRID_Y  50

#define OPTION_STATE 1
#define RUNNING_STATE 2
#define OVER_STATE 3
#define MAIN_STATE 0

#define OBJECT_SIZE SCREEN_WIDTH / N

#define APPLE_SCORE 1
#define APPLEBASKET_SCORE 5
#define APPLE_FRE 4

#define SNOWLAND 0
#define FOREST 1
#define DESERT 2

#define EASY 220
#define MEDIUM 170
#define HARD 70

#define RECT_WIDTH  30
#define RECT_HEIGHT  200
#define RECT_SPEED 15

const char* WINDOW_TITLE = "SnakeGame";

struct Game_state{
    int state;
};

#endif
