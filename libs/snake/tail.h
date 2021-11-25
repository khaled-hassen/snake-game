#pragma once
#include <SDL/SDL.h>
#include "../utils/types.h"

typedef struct Tail
{
    struct Tail* next;
    SDL_Rect shape;
} Tail;

// Create the snake tail
Tail* Tail_create(int x, int y, int length, int width);

// free the memory used by the tail
void Tail_destroy(Tail* tail);

// draw the snake to the screen
void Tail_render(SDL_Surface* screen, Tail* tail, Uint32 color);

// move the snake according the passed velocity
void Tail_move(Tail* tail, Vector velocity);

// increase the tail length and return the new tail
Tail* Tail_increment(Tail* tail);