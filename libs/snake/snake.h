#pragma once

#include <SDL/SDL.h>
#include <stdbool.h>
#include "tail.h"
#include "../utils/types.h"
#include "../utils/config.h"

#define SNAKE_WIDTH CELL_SIZE
#define SNAKE_BASE_SPEED CELL_SIZE
#define CELLS_PER_SECOND 4

typedef struct
{
    SDL_Rect head;
    Tail* tail;
    int score;
    Vector velocity;
    Vector direction;
    Uint32 color;
} Snake;

// create the snake and orientate it right or left
Snake* Snake_create(int x, int y, SDL_Surface* screen, Orientation ori);

// move the snake according to its velocity (the frames param is used to move the snake fps independently)
void Snake_move(SDL_Surface* screen, Snake* snake, int frames);

// turn the snake using his direction
void Snake_turn(Snake* snake);

// free the snake from memory
void Snake_destroy(Snake** snake);

// increases the snake's score and length when eating an apple
void Snake_eat(Snake* snake);

// check if the snake dead or not
// the snake is dead if he hits a wall, his tail or another snake
// return the state
bool Snake_isDead(Snake* snake, Snake* other, SDL_Rect* walls);

