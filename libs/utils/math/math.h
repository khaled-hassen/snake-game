#pragma once

#include <SDL/SDL_video.h>
#include <stdbool.h>

// init the randomness seed
void Math_initSeed();

// return a random number in range [start, end]
int Math_randomInt(int start, int end);

// return if there is a collision between two shapes
bool Math_detectCollision(SDL_Rect shape, SDL_Rect other);