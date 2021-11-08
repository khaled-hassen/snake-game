#pragma once

#include <SDL/SDL.h>

#define APPLE_DIM 15

// generate and place the apple in a random place inside the given area
void Apple_generate(SDL_Surface* screen, SDL_Rect area);