#pragma once

#include <SDL/SDL.h>

#define APPLE_DIM 15

// generate and place the apple in a random place inside the given area
SDL_Rect Apple_generate(SDL_Rect area);

void Apple_draw(SDL_Surface* screen, SDL_Rect apple);