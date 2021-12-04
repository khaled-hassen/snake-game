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
} Snake;

// create the snake
Snake* Snake_create(int x, int y);

// move the snake according the velocity
void Snake_move(SDL_Surface* screen, Snake* snake, int frames);

// turn the snake to the specified direction
void Snake_turn(Snake* snake);

// free the snake from memory
void Snake_destroy(Snake** snake);

// increases the snake's score and length when eating an apple
void Snake_eat(Snake* snake);

// check if the snake dead or not
// the snake is dead if he hits a wall or his tail
// return the state
bool Snake_isDead(Snake* snake, SDL_Rect* walls);

