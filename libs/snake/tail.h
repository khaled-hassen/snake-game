#pragma once

#include <SDL/SDL_video.h>
#include "../utils/types.h"

typedef struct
{
    SDL_Rect* blocks;
    int length;
} Tail;

#define TAIL_INITIAL_LENGTH 3
#define MAX_TAIL_INITIAL_LENGTH 100

// Create the snake tail
Tail* Tail_create(int x, int y, int width, Orientation ori);

// free the memory used by the tail
void Tail_destroy(Tail* tail);

// draw the snake to the screen
void Tail_render(SDL_Surface* screen, Tail* tail, Uint32 color);

// move the snake according the passed velocity
void Tail_move(SDL_Rect head, Tail* tail);

// increase the tail length and return the new tail
void Tail_increment(Tail* tail);