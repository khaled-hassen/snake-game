#pragma once

#include <SDL/SDL.h>
#include "../utils/config.h"

#define APPLE_SIZE CELL_SIZE

// generate and place the apple in a random place inside the given area
SDL_Rect Apple_spawn(SDL_Rect area);

void Apple_draw(SDL_Surface* screen, SDL_Rect apple);