#pragma once

#include <SDL/SDL.h>
#include <stdbool.h>
#include "../utils/types.h"
#include "../utils/config.h"

#define SNAKE_WIDTH CELL_SIZE
#define SNAKE_SPEED CELL_SIZE
#define SNAKE_INITIAL_LENGTH 3
#define CELLS_PER_SECOND 4

typedef struct
{
    SDL_Rect head;
    RectList* tail;
    int length;
    int score;
    int speed;
    Vector velocity;
} Snake;

// create the snake
Snake* Snake_create(int x, int y);

// move the snake according the velocity
void Snake_move(SDL_Surface* screen, Snake* snake, int frames);

// turn the snake to the specified direction
void Snake_turn(Snake* snake, Vector direction);

// free the snake from memory
void Snake_destroy(Snake* snake);

// increases the snake's score and length when eating an apple
void Snake_eat(Snake* snake);

// check if the snake hits a wall or not
// return the state
bool Snake_hitWalls(Snake* snake, SDL_Rect* walls);

// stop the snake's movement
void Snake_stop(Snake* snake);

