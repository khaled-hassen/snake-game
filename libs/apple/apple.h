#pragma once

#include <SDL/SDL.h>
#include "../utils/config.h"
#include "../utils/types.h"

#define APPLE_SIZE CELL_SIZE

typedef struct
{
    SDL_Rect shape;
    Vector lastPosition;
} Apple;

Apple* Apple_Create();

// generate and place the apple in a random place inside the given area
void Apple_generatePosition(Apple* apple, SDL_Rect area);

void Apple_draw(SDL_Surface* screen, Apple* apple);

void Apple_Destroy(Apple* apple);