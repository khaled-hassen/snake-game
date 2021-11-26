#pragma once
#include <SDL/SDL.h>
#include "../utils/types.h"

// Create the snake tail
RectList* Tail_create(int x, int y, int length, int width);

// free the memory used by the tail
void Tail_destroy(RectList* tail);

// draw the snake to the screen
void Tail_render(SDL_Surface* screen, RectList* tail, Uint32 color);

// move the snake according the passed velocity
void Tail_move(RectList* tail, Vector velocity);

// increase the tail length and return the new tail
RectList* Tail_increment(RectList* tail);