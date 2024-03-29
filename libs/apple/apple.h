#pragma once

#include <SDL/SDL.h>
#include "../utils/config.h"
#include "../snake/snake.h"
#include "../utils/types.h"

#define APPLE_SIZE CELL_SIZE

typedef struct
{
    SDL_Rect shape;
    Vector lastPosition;
} Apple;

Apple* Apple_Create();

// generate and place the apple in a random place inside the given area
// and prevent it from colliding with head the snake
void Apple_generatePosition(Apple* apple, SDL_Rect area, Snake* snake1, Snake* snake2);

// draws the apple to the screen
void Apple_draw(SDL_Surface* screen, Apple* apple);

// free the apple from memory
void Apple_destroy(Apple** apple);